#pragma once

#include <assimp/scene.h>

#include <string>

#include "aabb.hpp"
#include "mesh.hpp"
#include "material.hpp"

#include "asset_store.hpp"

class Model {
public:
    CullingAABB aabb() const;

private:
    std::string m_path;

    std::vector<int> m_meshes;
    std::vector<int> m_materials;

    CullingAABB m_aabb{};

    Model() = default;
    Model(const std::string& path);

    void loadModel(const std::string& path);

    int processMesh(const aiMesh* mesh, const aiScene* scene);
    void processNode(const aiNode* node, const aiScene* scene);

    friend class SceneRenderer;
    friend class AssetStore<Model>;
};