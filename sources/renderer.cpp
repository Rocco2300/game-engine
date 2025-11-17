#include "renderer.hpp"

#include <GL/gl3w.h>

Renderer::Renderer(const Program& program, const FPSCamera& camera)
    : m_program{&program}
    , m_camera{&camera} {}

void Renderer::draw(const Mesh& mesh) {
    m_program->use();
    m_program->setUniformMat4("mvp", m_camera->transform());

    glBindVertexArray(mesh.m_vao);
    glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Renderer::draw(const Model& model) {
    m_program->use();
    m_program->setUniformMat4("mvp", m_camera->transform());

    for (int i = 0; i < model.m_meshes.size(); i++) {
        model.m_materials[i]->bind();
        m_program->setUniformMaterial(*model.m_materials[i]);
        draw(*model.m_meshes[i]);
    }
}