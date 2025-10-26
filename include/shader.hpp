#pragma once

#include <cstdint>
#include <string>

class Shader {
private:
    uint32_t m_id;

public:

private:
    std::string loadShaderSource(const std::string& name);
};