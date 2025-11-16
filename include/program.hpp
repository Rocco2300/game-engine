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
    void use();

    void setUniformBool(const std::string& name, bool value);
    void setUniformFloat(const std::string& name, float value);

    void setUniformVec3(const std::string& name, const glm::vec3& value);
    void setUniformMat4(const std::string& name, const glm::mat4& value);

    void setUniformTexture(const std::string& name, const Texture& texture);
    void setUniformMaterial(const Material& material);
};