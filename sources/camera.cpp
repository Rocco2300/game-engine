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

glm::mat4 Camera::transform() {
    auto target     = m_position + m_direction;
    auto projection = glm::perspective(glm::radians(m_fov), m_aspect, 0.1f, 100.f);
    auto view       = glm::lookAt(m_position, target, m_up);

    return projection * view;
}

void Camera::move(glm::vec3 delta) {
    m_position += delta;
}

void Camera::rotateOX(float angle) {
    auto rotation = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(1, 0, 0));

    auto newUp        = rotation * glm::vec4(m_up, 1.f);
    auto newDirection = rotation * glm::vec4(m_direction, 1.f);

    m_up        = glm::vec3(newUp);
    m_direction = glm::vec3(newDirection);
}

void Camera::rotateOY(float angle) {
    auto rotation = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 1, 0));

    auto newDirection = rotation * glm::vec4(m_direction, 1.f);

    m_direction = glm::vec3(newDirection);
}

void Camera::rotateOZ(float angle) {
    auto rotation = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));

    auto newUp        = rotation * glm::vec4(m_up, 1.f);
    auto newDirection = rotation * glm::vec4(m_direction, 1.f);

    m_up        = glm::vec3(newUp);
    m_direction = glm::vec3(newDirection);
}