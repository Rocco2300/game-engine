#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

static constexpr char* ShaderSourceDirectory = "C:\\Users\\grigo\\Repos\\game-engine\\shaders";

std::string Shader::loadShaderSource(const std::string &name) {
    auto path = std::string(ShaderSourceDirectory);
    path += "\\" + name;

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Cannot open file " << path << '\n';
        return "";
    }

    std::stringstream fileData;
    fileData << in.rdbuf();

    return fileData.str();
}

