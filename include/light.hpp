#pragma once

#include <glm/vec3.hpp>

class Light {
public:
    enum class Type : int {
        Directional = 0,
        Point,
        Spot
    };

    Light() = default;
    Light(Type type, const glm::vec3& position, const glm::vec3& direction);

private:
    Type m_type;
    glm::vec3 m_position;
    glm::vec3 m_direction;

    friend class Program;
};