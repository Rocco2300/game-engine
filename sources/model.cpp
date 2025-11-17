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
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        glm::vec3 temp;
        temp.x = mesh->mVertices[i].x;
        temp.y = mesh->mVertices[i].y;
        temp.z = mesh->mVertices[i].z;
        vertex.position = temp;

        temp.x = mesh->mNormals[i].x;
        temp.y = mesh->mNormals[i].y;
        temp.z = mesh->mNormals[i].z;
        vertex.normal = temp;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 uv;
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = uv;
        }

        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* materialData = scene->mMaterials[mesh->mMaterialIndex];

        std::string path = "";
        auto material = std::make_unique<Material>();
        if (materialData->GetTextureCount(aiTextureType_NORMALS)) {
            aiString relativePath;
            materialData->GetTexture(aiTextureType_NORMALS, 0, &relativePath);
            path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
        }
        material->loadNormalTexture(path);

        path.clear();
        if (materialData->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString relativePath;
            materialData->GetTexture(aiTextureType_DIFFUSE, 0, &relativePath);
            path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
        }
        material->loadDiffuseTexture(path);

        path.clear();
        if (materialData->GetTextureCount(aiTextureType_SPECULAR)) {
            aiString relativePath;
            materialData->GetTexture(aiTextureType_SPECULAR, 0, &relativePath);
            path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
        }
        material->loadSpecularTexture(path);

        float str;
        aiColor3D color;
        materialData->Get(AI_MATKEY_COLOR_AMBIENT, color);
        material->setAmbient(getColor(color));

        materialData->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        material->setDiffuse(getColor(color));

        materialData->Get(AI_MATKEY_SPECULAR_FACTOR, str);
        materialData->Get(AI_MATKEY_COLOR_SPECULAR, color);
        material->setSpecular(getColor(color), str);

        m_materials.push_back(std::move(material));
    }

    return std::make_unique<Mesh>(vertices, indices);
}