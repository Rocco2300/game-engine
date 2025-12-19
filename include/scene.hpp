#pragma once

#include "entity.hpp"

#include <queue>
#include <iostream>
#include <vector>
#include <filesystem>
#include <unordered_map>

class Scene {
public:
    Scene();

    int getParent(int id);
    int addEntity(int parentId = -1);

    void setParent(int entity, int parent);

    Entity* getEntity(int id);

    void setEntities(const std::vector<Entity>& entities);
    void setParents(const std::unordered_map<int, int>& parents);

    const std::vector<Entity>& entities() const;
    const std::unordered_map<int, int>& parents() const;

private:
    friend class Serializer;

    std::queue<int> m_availableIds;
    std::vector<Entity> m_entities;
    std::unordered_map<int, int> m_parent;
};

namespace nlohmann {
    template <>
    struct adl_serializer<Scene> {
        static void to_json(json& j, const Scene& value) {
            j = json({
                    {"parent", value.parents()},
                    {"entities", value.entities()}
            });
        }

        static void from_json(const json& j, Scene& value) {
            std::vector<Entity> entities;
            std::unordered_map<int, int> parent;

            j.at("parent").get_to(parent);
            j.at("entities").get_to(entities);

            value.setParents(parent);
            value.setEntities(entities);
        }
    };
};