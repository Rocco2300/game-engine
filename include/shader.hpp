#pragma once

#include <cstdint>
#include <string>



class Shader {
public:
    friend class Program;

    enum class Type {
        Vertex,
        Fragment,
        Geometry,
        Compute
    };

private:
    uint32_t m_id;

public:
    Shader() = default;
    Shader(Type type, const std::string& fileName);
    ~Shader();

private:
    std::string loadShaderSource(const std::string& fileName);
    void compileShader(int32_t type, const std::string& source);

    int32_t getShaderType(Type type);
};