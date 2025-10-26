#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/gl3w.h>

static constexpr char ShaderSourceDirectory[] = "C:\\Users\\grigo\\Repos\\game-engine\\shaders";

Shader::Shader(Shader::Type type, const std::string& fileName) {
    auto intType = getShaderType(type);
    auto source  = loadShaderSource(fileName);

    compileShader(intType, source);
}

Shader::~Shader() {
    glDeleteShader(m_id);
}

std::string Shader::loadShaderSource(const std::string& fileName) {
    auto path = std::string(ShaderSourceDirectory);
    path += "\\" + fileName;

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Cannot open file " << path << '\n';
        return "";
    }

    std::stringstream fileData;
    fileData << in.rdbuf();

    return fileData.str();
}

void Shader::compileShader(int32_t type, const std::string& source) {
    m_id                   = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(m_id, 1, &sourceCStr, nullptr);
    glCompileShader(m_id);

    int compileStatus;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        char log[512];
        glGetShaderInfoLog(m_id, 512, nullptr, log);
        std::cerr << "Shader compilation failed:\n" << log << "\n";
    }
}

int32_t Shader::getShaderType(Type type) {
    switch (type) {
    case Type::Vertex:
        return GL_VERTEX_SHADER;
    case Type::Fragment:
        return GL_FRAGMENT_SHADER;
    default:
        return -1;
    }
}
