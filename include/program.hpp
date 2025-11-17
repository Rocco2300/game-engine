#pragma once

#include <glm/mat4x4.hpp>

#include "shader.hpp"

class Texture;
class Material;

class Program {
private:
    uint32_t m_id{};

public:
    Program();
    ~Program();

    void attachShader(Shader shader);
    void link();
    void use() const;

    void setUniformBool(const std::string& name, bool value) const;
    void setUniformFloat(const std::string& name, float value) const;

    void setUniformVec3(const std::string& name, const glm::vec3& value) const;
    void setUniformMat4(const std::string& name, const glm::mat4& value) const;

    void setUniformTexture(const std::string& name, const Texture& texture) const;
    void setUniformMaterial(const Material& material) const;
};