#include "asset_manager.hpp"

std::string AssetManager::m_path{};

AssetStore<Mesh> AssetManager::m_meshes{};
AssetStore<Model> AssetManager::m_models{};
AssetStore<Texture> AssetManager::m_textures{};
AssetStore<Material> AssetManager::m_materials{};

void AssetManager::setPath(const std::string& path) {
    m_path = path;

    m_meshes    = AssetStore<Mesh>(path);
    m_models    = AssetStore<Model>(path);
    m_textures  = AssetStore<Texture>(path);
    m_materials = AssetStore<Material>(path);
}

Model* AssetManager::getModel(int id) { return m_models.get(id); }

int AssetManager::loadModel(const std::string& name) { return m_models.load(name); }
