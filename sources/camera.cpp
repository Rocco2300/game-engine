#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float fov, float aspect) {
    m_fov = fov;
    m_aspect = aspect;

    m_position = position;

    m_up = glm::vec3(0, 1, 0);
    m_direction = glm::vec3(0, 0, -1);
}

glm::mat4 Camera::transform() {
    glm::mat4 transform = glm::mat4(1.f);

    auto target = m_position + m_direction;
    transform *= glm::perspective(m_fov, m_aspect, 0.1f, 100.f);
    transform *= glm::lookAt(m_position, target, m_up);

    return transform;
}