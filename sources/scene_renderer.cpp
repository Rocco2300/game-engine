#include "scene_renderer.hpp"

#include "asset_manager.hpp"

#include <GL/gl3w.h>

SceneRenderer::SceneRenderer()
    : IRenderer<Scene>("C:/Users/grigo/Repos/game-engine/shaders", "test") {}

SceneRenderer::SceneRenderer(const FPSCamera& camera, const Light& light)
    : IRenderer<Scene>("C:/Users/grigo/Repos/game-engine/shaders", "test")
    , m_camera{&camera}
    , m_light{&light} {}

static glm::mat4 getTransform(const Scene& scene, int id) {
    if (!scene.getEntity(id)) {
        return glm::mat4(1.f);
    }

    auto transform = getTransform(scene, scene.getParent(id));

    return transform * scene.getEntity(id)->transform();
}

void SceneRenderer::draw(const Scene& scene) {
    m_program.use();

    m_program.setUniformLight(*m_light);
    m_program.setUniformCamera(*m_camera);

    for (const auto& entity: scene.entities()) {
        auto transform = getTransform(scene, entity.id);

        m_program.setUniformMat4("model", transform);

        auto* model = AssetManager::getModel(entity.modelId);
        if (model) {
            drawModelImpl(*model);
        }
    }
}

void SceneRenderer::drawMeshImpl(const Mesh& mesh) {
    glBindVertexArray(mesh.m_vao);
    glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void SceneRenderer::drawModelImpl(const Model& model) {
    for (int i = 0; i < model.m_meshes.size(); i++) {
        auto materialId   = model.m_materials[i];
        auto materialData = AssetManager::getMaterial(materialId);

        materialData->bind();
        m_program.setUniformMaterial(*materialData);

        auto meshId   = model.m_meshes[i];
        auto meshData = AssetManager::getMesh(meshId);

        drawMeshImpl(*meshData);
    }
}