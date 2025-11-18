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
    std::vector<Mesh> m_meshes;
    std::vector<Material> m_materials;

private:
    Model() = default;
    Model(const std::string& path);

    void loadModel(const std::string& path);

    void processNode(const aiNode* node, const aiScene* scene);
    Mesh processMesh(const aiMesh* mesh, const aiScene* scene);

    friend class Renderer;
    friend class AssetStore<Model>;
};