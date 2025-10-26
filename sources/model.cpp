#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::draw() {
    for (const auto& mesh : m_meshes) {
        mesh->draw();
    }
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model file " << path << '\n';
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode* node, const aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        auto* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
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

    return std::make_unique<Mesh>(vertices, indices);
}