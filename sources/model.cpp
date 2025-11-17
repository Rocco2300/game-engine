#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model file " << path << '\n';
        return;
    }

    auto index = path.rfind("/");
    m_path = path.substr(0, index + 1);

    processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode* node, const aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        std::cout << "Loading mesh " << scene->mMeshes[node->mMeshes[i]]->mName.C_Str() << '\n';
        auto* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

static glm::vec3 getColor(aiColor3D color) {
    glm::vec3 ret;

    ret.r = color.r;
    ret.g = color.g;
    ret.b = color.b;

    return ret;
}

std::unique_ptr<Mesh> Model::processMesh(const aiMesh* mesh, const aiScene* scene) {
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* materialData = scene->mMaterials[mesh->mMaterialIndex];
        m_materials.push_back(std::make_unique<Material>(materialData));
    }

    return std::make_unique<Mesh>(mesh);
}