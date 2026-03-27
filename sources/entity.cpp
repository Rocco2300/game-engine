#include "entity.hpp"

#include "asset_manager.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Entity::transform() const {
    auto scaleTransform = glm::scale(glm::mat4(1.f), scale);
    auto rotationTransform = glm::translate(glm::mat4(1.f), rotation);
    auto translateTransform = glm::translate(glm::mat4(1.f), position);

    return translateTransform * rotationTransform * scaleTransform;
}

AABB generateAABBFromMesh(const Entity* entity) {
    auto* model = AssetManager::getModel(entity->modelId);

    if (model->meshes() == 0 || model->meshes() > 1) {
        return {};
    }

    int meshId = model->mesh(0);
    auto* mesh = AssetManager::getMesh(meshId);

    return mesh->aabb();
}

void printAABB(const Entity* entity) {
    auto* model = AssetManager::getModel(entity->modelId);

    if (model->meshes() == 0 || model->meshes() > 1) {
        std::cout << "Model doesn't have just one mesh!\n";
        return;
    }

    auto* mesh = AssetManager::getMesh(model->mesh(0));
    auto aabb  = mesh->aabb();
    std::cout << aabb.x << ' ' << aabb.y << ' ' << aabb.z << '\n';
}