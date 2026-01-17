#pragma once

#include "model.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "fps_camera.hpp"

class SceneRenderer : public IRenderer {
public:
    SceneRenderer();
    SceneRenderer(const FPSCamera& camera, const Light& light);

    void draw(const IDrawable& drawable) const override;

private:
    void drawMeshImpl(const Mesh& mesh) const;
    void drawModelImpl(const Model& model) const;

    Light const* m_light;
    FPSCamera const* m_camera;
};
