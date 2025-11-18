#pragma once

#include "texture.hpp"
#include "asset_store.hpp"

#include <assimp/material.h>

#include <glm/vec3.hpp>

class Material {
private:
    int m_normalTexture;
    int m_diffuseTexture;
    int m_specularTexture;

    bool m_hasNormalTexture{};
    bool m_hasDiffuseTexture{};
    bool m_hasSpecularTexture{};

    glm::vec3 m_ambient{};
    glm::vec3 m_diffuse{};
    glm::vec3 m_specular{};
    float m_specularStrength{};

private:
    Material() = default;
    Material(const aiMaterial* material);

public:
    void bind() const;

    void setAmbient(const glm::vec3& color);
    void setDiffuse(const glm::vec3& color);
    void setSpecular(const glm::vec3& color, float strength);

    void loadNormalTexture(const std::string& path = "");
    void loadDiffuseTexture(const std::string& path = "");
    void loadSpecularTexture(const std::string& path = "");

private:
    friend class Program;
    friend class AssetStore<Material>;
};