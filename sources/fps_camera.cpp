#include "fps_camera.hpp"

#include "input.hpp"

#include <glfw/glfw3.h>

FPSCamera::FPSCamera(glm::vec3 position, float fov, float aspect)
    : m_camera(position, fov, aspect), m_speed(3.f), m_slowSpeed(3.f), m_fastSpeed(12.f) {}

void FPSCamera::update(float dt) {
    if (Input::keyHeld(GLFW_KEY_LEFT_SHIFT)) {
        m_speed = m_fastSpeed;
    } else {
        m_speed = m_slowSpeed;
    }

    if (Input::keyHeld(GLFW_KEY_W)) {
        m_camera.move(glm::vec3(0, 0, 1) * -m_speed * dt);
    }

    if (Input::keyHeld(GLFW_KEY_S)) {
        m_camera.move(glm::vec3(0, 0, 1) * m_speed * dt);
    }

    if (Input::keyHeld(GLFW_KEY_A)) {
        m_camera.move(glm::vec3(1, 0, 0) * -m_speed * dt);
    }

    if (Input::keyHeld(GLFW_KEY_D)) {
        m_camera.move(glm::vec3(1, 0, 0) * m_speed * dt);
    }

    if (Input::keyHeld(GLFW_KEY_Q)) {
        m_camera.move(glm::vec3(0, 1, 0) * m_speed * dt);
    }

    if (Input::keyHeld(GLFW_KEY_E)) {
        m_camera.move(glm::vec3(0, 1, 0) * -m_speed * dt);
    }
}

glm::mat4 FPSCamera::transform() {
    return m_camera.transform();
}