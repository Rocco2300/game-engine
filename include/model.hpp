#pragma once

#include <assimp/scene.h>

#include <string>

#include "mesh.hpp"
#include "material.hpp"

#include "asset_store.hpp"

class Model {
public:
    int meshes() const;
    int mesh(int index) const;

private:
    std::string m_path;

    std::vector<int> m_meshes;
    std::vector<int> m_materials;

    Model() = default;
    Model(const std::string& path);

    void loadModel(const std::string& path);

    int processMesh(const aiMesh* mesh, const aiScene* scene);
    void processNode(const aiNode* node, const aiScene* scene);

    friend class SceneRenderer;
    friend class AssetStore<Model>;
};