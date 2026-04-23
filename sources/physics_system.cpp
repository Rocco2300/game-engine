#include "physics_system.hpp"

#include "entity.hpp"

void PhysicsSystem::onRegister(std::vector<Entity>& entities) {
    m_entities = &entities;
}

void PhysicsSystem::onAttach() {

}

void PhysicsSystem::onDetach() {

}

struct CollisionData {
    bool collided;
    glm::vec3 resolutionVector;
};

CollisionData isColliding(const Entity& a, const Entity& b) {
    auto aabb1 = static_cast<glm::vec3>(a.aabb);
    auto aabb2 = static_cast<glm::vec3>(b.aabb);
    auto& center1 = a.position;
    auto& center2 = b.position;

    auto centerDelta = center2 - center1;
    auto overlap     = (aabb1 + aabb2) - glm::abs(centerDelta);

    if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0) {
        if (overlap.x < overlap.y && overlap.x < overlap.z) {
            return {true, {centerDelta.x > 0 ? -overlap.x : overlap.x, 0, 0}};
        }

        if (overlap.y < overlap.z && overlap.y < overlap.x) {
            return {true, {0, centerDelta.y > 0 ? -overlap.y : overlap.y, 0}};
        }

        if (overlap.z < overlap.x && overlap.z < overlap.y) {
            return {true, {0, 0, centerDelta.z > 0 ? -overlap.z : overlap.z}};
        }
    }

    return {false, {0, 0, 0}};
}

void PhysicsSystem::onUpdate(float deltaTime) {
    for (int i = 0; i < m_entities->size(); i++) {
        for (int j = i + 1; j < m_entities->size(); j++) {
            auto hasAABB1 = glm::length(static_cast<glm::vec3>(m_entities->at(i).aabb)) != 0.0f;
            auto hasAABB2 = glm::length(static_cast<glm::vec3>(m_entities->at(j).aabb)) != 0.0f;
            if (!hasAABB1 || !hasAABB2) {
                continue;
            }

            auto collisionData = isColliding(m_entities->at(i), m_entities->at(j));
            if (collisionData.collided) {
                m_entities->at(i).position += collisionData.resolutionVector;
            }
        }
    }
}