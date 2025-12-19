#pragma once

#include "asset_store.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "serializer.hpp"

#include <tuple>
#include <utility>
#include <cstddef>
#include <iostream>
#include <filesystem>

class AssetManager {
public:
    static void setPath(const std::filesystem::path& path);

    static Mesh* getMesh(int id);
    static Model* getModel(int id);
    static Texture* getTexture(int id);
    static Material* getMaterial(int id);

    template <typename ...Args>
    static int loadMesh(const std::string& name, Args... args) {
        return m_meshes.emplace(name, args...);
    }

    template <typename ...Args>
    static int loadModel(const std::string& name, Args... args) {
        if (!m_models.get(name)) {
            Serializer::serializeAssetName("model", name);
        }

        return m_models.load(name, args...);
    }

    template <typename ...Args>
    static int loadTexture(const std::string& name, Args... args) {
        if (!m_textures.get(name)) {
            constexpr int argsNo = sizeof...(args);
            auto argsTuple = std::tie(args...);

            std::string textureTypeStr = "diffuse";
            if (argsNo > 0) {
                auto textureType = std::get<0>(argsTuple);
                switch (textureType) {
                case Texture::Type::Diffuse:
                    textureTypeStr = "diffuse";
                    break;
                case Texture::Type::Normal:
                    textureTypeStr = "normal";
                    break;
                case Texture::Type::Specular:
                    textureTypeStr = "specular";
                    break;
                }
            }

            Serializer::serializeAssetName("texture", name, textureTypeStr);
        }

        auto id = m_textures.load(name, args...);
        return id;
    }

    template <typename ...Args>
    static int emplaceTexture(const std::string& name, Args... args) {
        return m_textures.emplace(name, args...);
    }

    template <typename ...Args>
    static int loadMaterial(const std::string& name, Args... args) {
        return m_materials.emplace(name, args...);
    }

private:
    static std::filesystem::path m_path;

    static AssetStore<Mesh> m_meshes;
    static AssetStore<Model> m_models;
    static AssetStore<Texture> m_textures;
    static AssetStore<Material> m_materials;
};