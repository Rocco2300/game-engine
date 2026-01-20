#pragma once

#include "entity.hpp"
#include "layer.hpp"

#include <queue>
#include <iostream>
#include <vector>
#include <filesystem>
#include <unordered_map>

class Scene : public ILayer {
public:
    Scene();

    int getParent(int id) const;
    Entity* getEntity(int id);
    const Entity* getEntity(int id) const;

    int addEntity(int parentId = -1);
    void setParent(int entity, int parent);

    void setEntities(const std::vector<Entity>& entities);
    void setParents(const std::unordered_map<int, int>& parents);

    void removeEntity(int id);

    const std::vector<Entity>& entities() const;
    const std::unordered_map<int, int>& parents() const;

    void onAttach() override;
    void onDetach() override;

    void onDraw(const IRenderer& renderer) const override;
    void onUpdate(float deltaTime) override;

    void onEvent(const Event& event) override;

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