#pragma once

#include "entity.hpp"

#include <queue>
#include <vector>
#include <unordered_map>

class Scene {
public:
    Scene();

    int getParent(int id);
    int addEntity(int parentId = -1);

    void setParent(int entity, int parent);

    Entity* getEntity(int id);

    std::vector<Entity>* entities();

private:
    std::queue<int> m_availableIds;
    std::vector<Entity> m_entities;
    std::unordered_map<int, int> m_parent;
};