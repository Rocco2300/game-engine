#pragma once

#include "model.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "fps_camera.hpp"

class SceneRenderer : IRenderer<Scene> {
public:
    SceneRenderer();
    SceneRenderer(const FPSCamera& camera, const Light& light);

    void draw(const Mesh& mesh);
    void draw(const Model& model);
    void draw(const Scene& scene) override;
    void draw(const Entity& entity);

private:
    void drawMeshImpl(const Mesh& mesh);
    void drawModelImpl(const Model& model, glm::mat4 transform);

    Light const* m_light;
    FPSCamera const* m_camera;
};
