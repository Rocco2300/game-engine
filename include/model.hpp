#pragma once

#include <assimp/scene.h>

#include <string>

#include "mesh.hpp"
#include "material.hpp"

#include "asset_store.hpp"

class Model {
private:
    std::string m_path;
    // TODO: bypass lack of default constructor
    std::vector<int> m_meshes;
    std::vector<int> m_materials;

    Model() = default;
    Model(const std::string& path);

    void loadModel(const std::string& path);

    int processMesh(const aiMesh* mesh, const aiScene* scene);
    void processNode(const aiNode* node, const aiScene* scene);

    friend class Renderer;
    friend class AssetStore<Model>;
};