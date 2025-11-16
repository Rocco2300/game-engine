#pragma once

#include "texture.hpp"

#include <glm/vec3.hpp>

#include <memory>

class Material {
private:
    std::unique_ptr<Texture> m_normalTexture;
    std::unique_ptr<Texture> m_diffuseTexture;
    std::unique_ptr<Texture> m_specularTexture;

    bool m_hasNormalTexture{};
    bool m_hasDiffuseTexture{};
    bool m_hasSpecularTexture{};

    glm::vec3 m_diffuse{};
    float m_specular{};

public:
    Material() = default;

    void bind();

    void setDiffuse(const glm::vec3& color);
    void setSpecular(float strength);

    void loadDiffuseTexture(const std::string& path = "");
    void loadSpecularTexture(const std::string& path = "");
    void loadNormalTexture(const std::string& path = "");

private:
    void bindTexture(Texture::Type type, Texture* texture);

private:
    friend class Program;
};