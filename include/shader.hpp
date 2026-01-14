#pragma once

#include <string>
#include <cstdint>
#include <filesystem>

class Shader {
public:
    enum class Type {
        Vertex,
        Fragment,
        Geometry,
        Compute
    };

    Shader() = default;
    Shader(Type type, const std::filesystem::path& path);
    ~Shader();

private:
    friend class Program;

    std::string loadShaderSource(const std::filesystem::path& path);
    void compileShader(int32_t type, std::string_view source);

    int32_t getShaderType(Type type);

    uint32_t m_id{};
};