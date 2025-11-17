#pragma once

#include "model.hpp"
#include "program.hpp"
#include "fps_camera.hpp"

class Renderer {
private:
    Program const* m_program;
    FPSCamera const* m_camera;

public:
    Renderer() = default;
    Renderer(const Program& program, const FPSCamera& camera);

    void draw(const Mesh& mesh);
    void draw(const Model& model);
};