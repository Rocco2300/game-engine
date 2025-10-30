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
        auto velocity = m_camera.m_direction * m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_S)) {
        auto velocity = m_camera.m_direction * -m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_A)) {
        auto direction = glm::cross(m_camera.m_direction, glm::vec3(0, 1, 0));
        auto velocity = direction * -m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_D)) {
        auto direction = glm::cross(m_camera.m_direction, glm::vec3(0, 1, 0));
        auto velocity = direction * m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_Q)) {
        auto velocity = glm::vec3(0, 1, 0) * m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_E)) {
        auto velocity = glm::vec3(0, 1, 0) * -m_speed * dt;
        m_camera.move(velocity);
    }
}

glm::mat4 FPSCamera::transform() {
    return m_camera.transform();
}