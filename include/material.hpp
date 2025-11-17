#pragma once

#include "texture.hpp"

#include <assimp/material.h>

#include <glm/vec3.hpp>

class Material {
private:
    Texture m_normalTexture;
    Texture m_diffuseTexture;
    Texture m_specularTexture;

    bool m_hasNormalTexture{};
    bool m_hasDiffuseTexture{};
    bool m_hasSpecularTexture{};

    glm::vec3 m_ambient{};
    glm::vec3 m_diffuse{};
    glm::vec3 m_specular{};
    float m_specularStrength{};

public:
    Material() = default;
    Material(const aiMaterial* material);

    void bind() const;

    void setAmbient(const glm::vec3& color);
    void setDiffuse(const glm::vec3& color);
    void setSpecular(const glm::vec3& color, float strength);

    void loadNormalTexture(const std::string& path = "");
    void loadDiffuseTexture(const std::string& path = "");
    void loadSpecularTexture(const std::string& path = "");

private:
    void bindTexture(Texture::Type type, Texture* texture);

private:
    friend class Program;
};