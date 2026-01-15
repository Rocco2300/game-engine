#include "asset_manager.hpp"

std::filesystem::path AssetManager::m_path{};

AssetStore<Mesh> AssetManager::m_meshes{};
AssetStore<Model> AssetManager::m_models{};
AssetStore<MaterialTexture> AssetManager::m_materialTextures{};
AssetStore<Material> AssetManager::m_materials{};

void AssetManager::setPath(const std::filesystem::path& path) {
    m_path = path;

    m_meshes           = AssetStore<Mesh>(path);
    m_models           = AssetStore<Model>(path);
    m_materialTextures = AssetStore<MaterialTexture>(path);
    m_materials        = AssetStore<Material>(path);
}

Mesh* AssetManager::getMesh(int id) { return m_meshes.get(id); }

Model* AssetManager::getModel(int id) { return m_models.get(id); }

MaterialTexture* AssetManager::getTexture(int id) { return m_materialTextures.get(id); }

Material* AssetManager::getMaterial(int id) { return m_materials.get(id); }