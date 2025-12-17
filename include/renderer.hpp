#pragma once

#include "model.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "program.hpp"
#include "fps_camera.hpp"

class Renderer {
public:
    Renderer() = default;
    Renderer(const Program& program, const FPSCamera& camera, const Light& light);

    void draw(const Mesh& mesh);
    void draw(const Model& model);
    void draw(Scene& scene);
    void draw(const Entity& entity);

private:
    void drawMeshImpl(const Mesh& mesh);
    void drawModelImpl(const Model& model, glm::mat4 transform);

    Light const* m_light;
    Program const* m_program;
    FPSCamera const* m_camera;
};