#include "scene.hpp"

#include "scene_renderer.hpp"

Scene::Scene() {
    for (int i = 0; i <= 256; i++) {
        m_availableIds.push(i);
    }
}

Entity* Scene::getEntity(int id) {
    for (auto& entity : m_entities) {
        if (entity.id == id) {
            return &entity;
        }
    }

    return nullptr;
}

const Entity* Scene::getEntity(int id) const {
    for (auto& entity : m_entities) {
        if (entity.id == id) {
            return &entity;
        }
    }

    return nullptr;
}

int Scene::getParent(int id) const {
    if (!m_parent.count(id) || m_parent.at(id) == -1) {
        return -1;
    }

    return m_parent.at(id);
}

int Scene::addEntity(int parentId) {
    auto id = m_availableIds.front();
    m_availableIds.pop();
    Entity entity{
        .id =  id
    };

    m_entities.push_back(entity);
    setParent(id, parentId);

    return id;
}

void Scene::setParent(int entity, int parent) {
    if (!getEntity(entity) || !getParent(entity)) {
        return;
    }

    m_parent.emplace(entity, parent);
}

void Scene::setEntities(const std::vector<Entity>& entities) {
    m_entities = entities;
}

void Scene::setParents(const std::unordered_map<int, int>& parents) {
    m_parent = parents;
}

const std::vector<Entity>& Scene::entities() const {
    return m_entities;
}

const std::unordered_map<int, int>& Scene::parents() const {
    return m_parent;
}

void Scene::onAttach() {

}

void Scene::onDetach() {

}

void Scene::onDraw(const IRenderer& renderer) const {
    renderer.draw(*this);
}

void Scene::onUpdate(float deltaTime) {

}

void Scene::onEvent(int event) {

}