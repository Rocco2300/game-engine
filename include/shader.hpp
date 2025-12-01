#pragma once

#include <cstdint>
#include <string>



class Shader {
public:
    enum class Type {
        Vertex,
        Fragment,
        Geometry,
        Compute
    };

    Shader() = default;
    Shader(Type type, const std::string& fileName);
    ~Shader();

private:
    friend class Program;

    std::string loadShaderSource(const std::string& fileName);
    void compileShader(int32_t type, const std::string& source);

    int32_t getShaderType(Type type);

    uint32_t m_id{};
};