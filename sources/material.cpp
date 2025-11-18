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
    aiString relativePath{};
    if (material->GetTextureCount(aiTextureType_NORMALS)) {
        material->GetTexture(aiTextureType_NORMALS, 0, &relativePath);
    }
    loadNormalTexture(relativePath.C_Str());

    relativePath.Clear();
    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
        material->GetTexture(aiTextureType_DIFFUSE, 0, &relativePath);
    }
    loadDiffuseTexture(relativePath.C_Str());

    relativePath.Clear();
    if (material->GetTextureCount(aiTextureType_SPECULAR)) {
        material->GetTexture(aiTextureType_SPECULAR, 0, &relativePath);
    }
    loadSpecularTexture(relativePath.C_Str());

    float str;
    aiColor3D color;
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    setAmbient(getColor(color));

    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    setDiffuse(getColor(color));

    material->Get(AI_MATKEY_SPECULAR_FACTOR, str);
    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    setSpecular(getColor(color), str);
}

void Material::bind() const {
    auto normalTexture = AssetManager::getTexture(m_normalTexture);
    auto diffuseTexture = AssetManager::getTexture(m_diffuseTexture);
    auto specularTexture = AssetManager::getTexture(m_specularTexture);

    normalTexture->bind();
    diffuseTexture->bind();
    specularTexture->bind();
}

void Material::setAmbient(const glm::vec3& color) {
    m_ambient = color;
}

void Material::setDiffuse(const glm::vec3& color) {
    m_diffuse = color;
}

void Material::setSpecular(const glm::vec3& color, float strength) {
    m_specular = color;
    m_specularStrength = strength;
}

void Material::loadNormalTexture(const std::string& path) {
    m_hasNormalTexture = !path.empty();
    m_normalTexture = AssetManager::loadTexture(path, Texture::Type::Normal);
}

void Material::loadDiffuseTexture(const std::string& path) {
    m_hasDiffuseTexture = !path.empty();
    m_diffuseTexture = AssetManager::loadTexture(path, Texture::Type::Diffuse);
}

void Material::loadSpecularTexture(const std::string& path) {
    m_hasSpecularTexture = !path.empty();
    m_specularTexture = AssetManager::loadTexture(path, Texture::Type::Specular);
}