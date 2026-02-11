#pragma once

#include "asset_store.hpp"
#include "material_texture.hpp"

#include <assimp/material.h>

#include <filesystem>

class Material {
public:
    void bind() const;

    void setSpecularStrength(float strength);

    void loadNormalTexture(const std::string& path = "");
    void loadNormalTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber);

    void loadDiffuseTexture(const std::string& path = "");
    void loadDiffuseTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber);

    void loadSpecularTexture(const std::string& path = "");
    void loadSpecularTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber);

private:
    friend class Program;
    friend class AssetStore<Material>;

    Material() = default;
    Material(const aiMaterial* material);

    int m_normalTexture;
    int m_diffuseTexture;
    int m_specularTexture;

    bool m_hasNormalTexture{};
    float m_specularStrength{};
};