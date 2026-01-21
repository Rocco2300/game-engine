#include "material.hpp"

#include "asset_manager.hpp"

#include <iostream>

static glm::vec3 getColor(aiColor3D color) {
    glm::vec3 ret;

    ret.r = color.r;
    ret.g = color.g;
    ret.b = color.b;

    return ret;
}

Material::Material(const aiMaterial* material) {
    aiColor3D color;
    aiString relativePath{};
    if (material->GetTextureCount(aiTextureType_NORMALS)) {
        m_hasNormalTexture = true;

        material->GetTexture(aiTextureType_NORMALS, 0, &relativePath);
        loadNormalTexture(relativePath.C_Str());
    } else {
        uint8_t* data = new uint8_t[3];
        data[0]       = 128;
        data[1]       = 128;
        data[2]       = 255;

        loadNormalTexture(data, 1, 1, 3);
    }

    relativePath.Clear();
    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
        material->GetTexture(aiTextureType_DIFFUSE, 0, &relativePath);
        loadDiffuseTexture(relativePath.C_Str());
    } else {
        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);

        uint8_t* data = new uint8_t[3];
        data[0]       = static_cast<uint8_t>(color.r * 255);
        data[1]       = static_cast<uint8_t>(color.g * 255);
        data[2]       = static_cast<uint8_t>(color.b * 255);

        loadDiffuseTexture(data, 1, 1, 3);
    }

    relativePath.Clear();
    if (material->GetTextureCount(aiTextureType_SPECULAR)) {
        material->GetTexture(aiTextureType_SPECULAR, 0, &relativePath);
        loadSpecularTexture(relativePath.C_Str());
    } else {
        material->Get(AI_MATKEY_COLOR_SPECULAR, color);

        uint8_t* data = new uint8_t[3];
        data[0]       = static_cast<uint8_t>(color.r * 255);
        data[1]       = static_cast<uint8_t>(color.g * 255);
        data[2]       = static_cast<uint8_t>(color.b * 255);

        loadSpecularTexture(data, 1, 1, 3);
    }

    float str;
    material->Get(AI_MATKEY_SPECULAR_FACTOR, str);
    setSpecularStrength(str);
}

void Material::bind() const {
    auto normalTexture   = AssetManager::getTexture(m_normalTexture);
    auto diffuseTexture  = AssetManager::getTexture(m_diffuseTexture);
    auto specularTexture = AssetManager::getTexture(m_specularTexture);

    normalTexture->bind();
    diffuseTexture->bind();
    specularTexture->bind();
}

void Material::setSpecularStrength(float strength) { m_specularStrength = strength; }

void Material::loadNormalTexture(const std::string& name) {
    m_normalTexture = AssetManager::loadMaterialTexture(name, MaterialTexture::Type::Normal);
}

void Material::loadNormalTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber) {
    // TODO: change name
    TextureData textureData {
            .width  = width,
            .height = height,
            .data   = data,
            .format = toTextureFormat(channelNumber)
    };

    m_normalTexture = AssetManager::emplaceMaterialTexture(
            "normal",
            textureData,
            MaterialTexture::Type::Normal
    );
}

void Material::loadDiffuseTexture(const std::string& name) {
    m_diffuseTexture = AssetManager::loadMaterialTexture(name, MaterialTexture::Type::Diffuse);
}

void Material::loadDiffuseTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber) {
    TextureData textureData {
            .width  = width,
            .height = height,
            .data   = data,
            .format = toTextureFormat(channelNumber)
    };

    m_diffuseTexture = AssetManager::emplaceMaterialTexture(
            "diffuse",
            textureData,
            MaterialTexture::Type::Diffuse
    );
}

void Material::loadSpecularTexture(const std::string& name) {
    m_specularTexture = AssetManager::loadMaterialTexture(name, MaterialTexture::Type::Specular);
}

void Material::loadSpecularTexture(uint8_t* data, uint32_t width, uint32_t height, int channelNumber) {
    TextureData textureData {
            .width  = width,
            .height = height,
            .data   = data,
            .format = toTextureFormat(channelNumber)
    };

    m_specularTexture = AssetManager::emplaceMaterialTexture(
            "specular",
            textureData,
            MaterialTexture::Type::Specular
    );
}