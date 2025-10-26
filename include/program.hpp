#pragma once

#include "shader.hpp"

class Program {
private:
    uint32_t m_id;

public:
    Program();
    ~Program();

    void attachShader(Shader shader);
    void link();
    void use();
};