#include "program.hpp"

#include <GL/gl3w.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


Program::Program() {
    m_id = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(m_id);
}

void Program::attachShader(Shader shader) {
    glAttachShader(m_id, shader.m_id);
}

void Program::link() {
    glLinkProgram(m_id);

    int linkStatus;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(m_id, 512, nullptr, log);
        std::cerr << "Program linking failed:\n" << log << "\n";
    }
}

void Program::use() {
    glUseProgram(m_id);
}

void Program::setUniformMat4(const std::string& name, const glm::mat4& value) {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniformMatrix4fv(m_id, location, 1, GL_FALSE, glm::value_ptr(value));
}