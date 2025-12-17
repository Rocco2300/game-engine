#pragma once

#include "model.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct Entity {
    int id{-1};
    int modelId{-1};

    glm::vec3 scale{1.f};
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};

    glm::mat4 transform() const;
};