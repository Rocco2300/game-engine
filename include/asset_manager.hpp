#pragma once

#include "asset_store.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "material.hpp"

class AssetManager {
private:
    static std::string m_path;

    static AssetStore<Mesh> m_meshes;
    static AssetStore<Model> m_models;
    static AssetStore<Texture> m_textures;
    static AssetStore<Material> m_materials;

public:
    static void setPath(const std::string& path);

    static Model* getModel(int id);

    static int loadModel(const std::string& name);
};