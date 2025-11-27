#include "program.hpp"

#include "texture.hpp"
#include "material.hpp"
#include "asset_manager.hpp"

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

void Program::use() const {
    glUseProgram(m_id);
}

void Program::setUniformInt(const std::string& name, int value) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform1i(m_id, location, value);
}

void Program::setUniformBool(const std::string& name, bool value) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform1i(m_id, location, value);
}

void Program::setUniformFloat(const std::string& name, float value) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform1f(m_id, location, value);
}

void Program::setUniformVec3(const std::string& name, const glm::vec3& value) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform3fv(m_id, location, 1, glm::value_ptr(value));
}

void Program::setUniformMat4(const std::string& name, const glm::mat4& value) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniformMatrix4fv(m_id, location, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::setUniformLight(const Light& light) const {
    setUniformInt("lightType", static_cast<int>(light.m_type));
    setUniformVec3("lightPosition", light.m_position);
    setUniformVec3("lightDirection", light.m_direction);
}

void Program::setUniformCamera(const FPSCamera& camera) const {
    setUniformVec3("viewPosition", camera.position());
    setUniformMat4("view", camera.view());
    setUniformMat4("projection", camera.projection());
}

void Program::setUniformTexture(const std::string& name, const Texture& texture) const {
    auto location = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform1i(m_id, location, texture.getBindUnit());
}

void Program::setUniformMaterial(const Material& material) const {
    auto normalTexture = AssetManager::getTexture(material.m_normalTexture);
    auto diffuseTexture = AssetManager::getTexture(material.m_diffuseTexture);
    auto specularTexture = AssetManager::getTexture(material.m_specularTexture);

    setUniformTexture("normalTexture", *normalTexture);
    setUniformTexture("diffuseTexture", *diffuseTexture);
    setUniformTexture("specularTexture", *specularTexture);
    setUniformFloat("specularStrength", material.m_specularStrength);
}