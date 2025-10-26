#include "program.hpp"

#include <iostream>

#include <GL/gl3w.h>

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