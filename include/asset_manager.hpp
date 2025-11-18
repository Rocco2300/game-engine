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

    static Mesh* getMesh(int id);
    static Model* getModel(int id);
    static Texture* getTexture(int id);
    static Material* getMaterial(ind id);

    template <typename ...Args>
    static int loadMesh(const std::string& name, Args... args) {
        return m_meshes.load(name, args...);
    }

    template <typename ...Args>
    static int loadModel(const std::string& name, Args... args) {
        return m_models.load(name, args...);
    }

    template <typename ...Args>
    static int loadTexture(const std::string& name, Args... args) {
        return m_textures.load(name, args...);
    }

    template <typename ...Args>
    static int loadMaterial(const std::string& name, Args... args) {
        return m_materials.load(name, args...);
    }
};