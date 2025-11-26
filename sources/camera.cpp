#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float fov, float aspect) {
    m_fov    = fov;
    m_aspect = aspect;

    m_position = position;

    m_up        = glm::vec3(0, 1, 0);
    m_direction = glm::vec3(0, 0, -1);
}

glm::vec3 Camera::position() const { return m_position; }

glm::mat4 Camera::view() const {
    auto target = m_position + m_direction;
    return glm::lookAt(m_position, target, m_up);
}

glm::mat4 Camera::projection() const {
    return glm::perspective(glm::radians(m_fov), m_aspect, 0.1f, 100.f);
}

glm::mat4 Camera::transform() const { return projection() * view(); }

void Camera::move(glm::vec3 delta) { m_position += delta; }

void Camera::rotate(glm::vec3 axis, float angle) {
    auto rotation = glm::rotate(glm::mat4(1), glm::radians(angle), axis);

    auto newUp        = rotation * glm::vec4(m_up, 1.f);
    auto newDirection = rotation * glm::vec4(m_direction, 1.f);

    m_up        = glm::vec3(newUp);
    m_direction = glm::vec3(newDirection);
}