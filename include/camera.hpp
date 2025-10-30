#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
    float m_fov{};
    float m_aspect{};

    glm::vec3 m_position{};

    glm::vec3 m_up{};
    glm::vec3 m_direction{};

public:
    Camera(glm::vec3 position, float fov, float aspect);

    glm::mat4 transform();

    void move(glm::vec3 delta);
    void rotateOX(float angle);
    void rotateOY(float angle);
    void rotateOZ(float angle);
};