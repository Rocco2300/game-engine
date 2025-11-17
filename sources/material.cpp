#include "material.hpp"

#include <iostream>

static glm::vec3 getColor(aiColor3D color) {
    glm::vec3 ret;

    ret.r = color.r;
    ret.g = color.g;
    ret.b = color.b;

    return ret;
}

Material::Material(const aiMaterial* material) {
    const std::string m_path = "C:/Users/grigo/Repos/game-engine/";
    std::string path = "";

    if (material->GetTextureCount(aiTextureType_NORMALS)) {
        aiString relativePath;
        material->GetTexture(aiTextureType_NORMALS, 0, &relativePath);
        path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
    }
    loadNormalTexture(path);

    path.clear();
    if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
        aiString relativePath;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &relativePath);
        path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
    }
    loadDiffuseTexture(path);

    path.clear();
    if (material->GetTextureCount(aiTextureType_SPECULAR)) {
        aiString relativePath;
        material->GetTexture(aiTextureType_SPECULAR, 0, &relativePath);
        path = (!relativePath.Empty()) ? m_path + relativePath.C_Str() : "";
    }
    loadSpecularTexture(path);

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
    m_normalTexture.bind();
    m_diffuseTexture.bind();
    m_specularTexture.bind();
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
    m_normalTexture = Texture(path, Texture::Type::Normal);
}

void Material::loadDiffuseTexture(const std::string& path) {
    m_hasDiffuseTexture = !path.empty();
    m_diffuseTexture = Texture(path, Texture::Type::Diffuse);
}

void Material::loadSpecularTexture(const std::string& path) {
    m_hasSpecularTexture = !path.empty();
    m_specularTexture = Texture(path, Texture::Type::Specular);
}