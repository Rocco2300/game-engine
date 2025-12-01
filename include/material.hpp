#pragma once

#include "texture.hpp"
#include "asset_store.hpp"

#include <assimp/material.h>

#include <glm/vec3.hpp>

#include <filesystem>

class Material {
public:
    void bind() const;

    void setSpecularStrength(float strength);

    void loadNormalTexture(const std::string& path = "");
    void loadNormalTexture(const uint8_t* data, int width, int height, int channelNumber);

    void loadDiffuseTexture(const std::string& path = "");
    void loadDiffuseTexture(const uint8_t* data, int width, int height, int channelNumber);

    void loadSpecularTexture(const std::string& path = "");
    void loadSpecularTexture(const uint8_t* data, int width, int height, int channelNumber);

private:
    friend class Program;
    friend class AssetStore<Material>;

    Material() = default;
    Material(const aiMaterial* material);

    int m_normalTexture;
    int m_diffuseTexture;
    int m_specularTexture;

    float m_specularStrength{};
};