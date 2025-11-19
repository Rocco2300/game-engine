#include "light.hpp"

Light::Light(Light::Type type, const glm::vec3& position, const glm::vec3& direction)
    : m_type{type}
    , m_position{position}
    , m_direction{direction} {}

