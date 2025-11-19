#pragma once

#include "model.hpp"
#include "light.hpp"
#include "program.hpp"
#include "fps_camera.hpp"

class Renderer {
public:
    Renderer() = default;
    Renderer(const Program& program, const FPSCamera& camera, const Light& light);

    void draw(const Mesh& mesh);
    void draw(const Model& model);

private:
    void drawMeshImpl(const Mesh& mesh);

    Light const* m_light;
    Program const* m_program;
    FPSCamera const* m_camera;
};