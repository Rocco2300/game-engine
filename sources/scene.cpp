#include "scene.hpp"

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

int Scene::getParent(int id){
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

std::vector<Entity>* Scene::entities() {
    return &m_entities;
}