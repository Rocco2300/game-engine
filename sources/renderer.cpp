#include "renderer.hpp"

#include "asset_manager.hpp"

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
        auto materialId   = model.m_materials[i];
        auto materialData = AssetManager::getMaterial(materialId);

        materialData->bind();
        m_program->setUniformMaterial(*materialData);

        auto meshId   = model.m_meshes[i];
        auto meshData = AssetManager::getMesh(meshId);

        draw(*meshData);
    }
}