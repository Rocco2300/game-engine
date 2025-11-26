#include "renderer.hpp"

#include "asset_manager.hpp"

#include <GL/gl3w.h>

Renderer::Renderer(const Program& program, const FPSCamera& camera, const Light& light)
    : m_program{&program}
    , m_camera{&camera}
    , m_light{&light} {}

void Renderer::draw(const Mesh& mesh) {
    m_program->use();
    m_program->setUniformLight(*m_light);
    m_program->setUniformCamera(*m_camera);

    drawMeshImpl(mesh);
}

void Renderer::draw(const Model& model) {
    m_program->use();
    m_program->setUniformLight(*m_light);
    m_program->setUniformCamera(*m_camera);

    for (int i = 0; i < model.m_meshes.size(); i++) {
        auto materialId   = model.m_materials[i];
        auto materialData = AssetManager::getMaterial(materialId);

        materialData->bind();
        m_program->setUniformMaterial(*materialData);

        auto meshId   = model.m_meshes[i];
        auto meshData = AssetManager::getMesh(meshId);

        drawMeshImpl(*meshData);
    }
}

void Renderer::drawMeshImpl(const Mesh& mesh) {
    glBindVertexArray(mesh.m_vao);
    glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}