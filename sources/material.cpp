#include "material.hpp"

#include <iostream>

void Material::bind() {
    m_normalTexture->bind();
    m_diffuseTexture->bind();
    m_specularTexture->bind();
}

void Material::setDiffuse(const glm::vec3& color) {
    m_diffuse = color;
}

void Material::setSpecular(float strength) {
    m_specular = strength;
}

void Material::loadNormalTexture(const std::string& path) {
    m_hasNormalTexture = !path.empty();
    m_normalTexture = std::make_unique<Texture>(Texture::Type::Normal, path);
}

void Material::loadDiffuseTexture(const std::string& path) {
    m_hasDiffuseTexture = !path.empty();
    m_diffuseTexture = std::make_unique<Texture>(Texture::Type::Diffuse, path);
}

void Material::loadSpecularTexture(const std::string& path) {
    m_hasSpecularTexture = !path.empty();
    m_specularTexture = std::make_unique<Texture>(Texture::Type::Specular, path);
}