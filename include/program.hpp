#pragma once

#include <glm/mat4x4.hpp>

#include "shader.hpp"

class Program {
private:
    uint32_t m_id{};

public:
    Program();
    ~Program();

    void attachShader(Shader shader);
    void link();
    void use();

    void setUniformMat4(const std::string& name, const glm::mat4& value);
};