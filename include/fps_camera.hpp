#pragma once

#include "camera.hpp"

class FPSCamera {
private:
    Camera m_camera;

    float m_speed;
    const float m_slowSpeed;
    const float m_fastSpeed;

public:
    FPSCamera(glm::vec3 position, float fov, float aspect);

    void update(float dt);

    glm::mat4 transform() const;
};