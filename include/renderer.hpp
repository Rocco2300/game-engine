#pragma once

#include "program.hpp"

template <typename T>
class IRenderer {
public:
    IRenderer() = delete;
    IRenderer(const std::filesystem::path& path, const std::string& name) {
        auto vertexName = name + ".vert";
        auto vertexPath = path / vertexName;

        auto fragmentName = name + ".frag";
        auto fragmentPath = path / fragmentName;

        Shader vertexShader(Shader::Type::Vertex, vertexPath);
        Shader fragmentShader(Shader::Type::Fragment, fragmentPath);

        m_program.attachShader(vertexShader);
        m_program.attachShader(fragmentShader);
        m_program.link();
    }

    virtual ~IRenderer() = default;

    virtual void draw(const T& drawable) = 0;

protected:
    Program m_program;
};
