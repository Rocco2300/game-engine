#include "entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Entity::transform() const {
    auto scaleTransform = glm::scale(glm::mat4(1.f), scale);
    auto rotationTransform = glm::translate(glm::mat4(1.f), rotation);
    auto translateTransform = glm::translate(glm::mat4(1.f), position);

    return translateTransform * rotationTransform * scaleTransform;
}