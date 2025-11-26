#include "fps_camera.hpp"

#include "input.hpp"

#include <glfw/glfw3.h>

#include <iostream>

FPSCamera::FPSCamera(glm::vec3 position, float fov, float aspect)
    : m_camera(position, fov, aspect)
    , m_speed(3.f)
    , m_slowSpeed(3.f)
    , m_fastSpeed(12.f) {}

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
        auto right    = glm::cross(m_camera.m_direction, glm::vec3(0, 1, 0));
        auto velocity = right * -m_speed * dt;
        m_camera.move(velocity);
    }

    if (Input::keyHeld(GLFW_KEY_D)) {
        auto right    = glm::cross(m_camera.m_direction, glm::vec3(0, 1, 0));
        auto velocity = right * m_speed * dt;
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

    if (Input::mouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        Input::hideCursor(true);
        Input::bindCursor(true);
    } else if (Input::mouseButtonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
        Input::hideCursor(false);
        Input::bindCursor(false);
    }

    if (Input::mouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
        auto right       = glm::cross(m_camera.m_direction, glm::vec3(0, 1, 0));
        auto cursorDelta = Input::cursorDelta();

        m_camera.rotate(right, -20.f * cursorDelta.y * dt);
        m_camera.rotate(glm::vec3(0, 1, 0), -20.f * cursorDelta.x * dt);
    }
}

glm::vec3 FPSCamera::position() const { return m_camera.position(); }

glm::mat4 FPSCamera::view() const { return m_camera.view(); }

glm::mat4 FPSCamera::projection() const { return m_camera.projection(); }

glm::mat4 FPSCamera::transform() const { return m_camera.transform(); }