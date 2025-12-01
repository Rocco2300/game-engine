#pragma once

#include "camera.hpp"

class FPSCamera {
public:
    FPSCamera(glm::vec3 position, float fov, float aspect);

    void update(float dt);

    glm::vec3 position() const;

    glm::mat4 view() const;
    glm::mat4 projection() const;
    glm::mat4 transform() const;

private:
    Camera m_camera;

    float m_speed;
    const float m_slowSpeed;
    const float m_fastSpeed;
};