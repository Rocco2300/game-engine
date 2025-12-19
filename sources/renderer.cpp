#include "renderer.hpp"

#include "asset_manager.hpp"

#include <GL/gl3w.h>

Renderer::Renderer(const Program& program, const FPSCamera& camera, const Light& light)
    : m_program{&program}
    , m_camera{&camera}
    , m_light{&light} {}

void Renderer::draw(const Mesh& mesh) {
    m_program->setUniformLight(*m_light);
    m_program->setUniformCamera(*m_camera);

    drawMeshImpl(mesh);
}

void Renderer::draw(const Model& model) {
    drawModelImpl(model, glm::mat4(1.f));
}

static glm::mat4 getTransform(Scene& scene, int id) {
    if (!scene.getEntity(id)) {
        return glm::mat4(1.f);
    }

    auto transform = getTransform(scene, scene.getParent(id));

    return transform * scene.getEntity(id)->transform();
}

void Renderer::draw(Scene& scene) {
    for (const auto& entity : scene.entities()) {
        auto transform = getTransform(scene, entity.id);

        auto* model = AssetManager::getModel(entity.modelId);
        if (model) {
            drawModelImpl(*model, transform);
        }
    }
}

void Renderer::draw(const Entity& entity) {
    auto* model = AssetManager::getModel(entity.modelId);
    drawModelImpl(*model, entity.transform());
}

void Renderer::drawMeshImpl(const Mesh& mesh) {
    m_program->use();

    glBindVertexArray(mesh.m_vao);
    glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Renderer::drawModelImpl(const Model& model, glm::mat4 transform) {
    m_program->setUniformLight(*m_light);
    m_program->setUniformCamera(*m_camera);
    m_program->setUniformMat4("model", transform);

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