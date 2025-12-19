#pragma once

#include "json.hpp"
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

namespace nlohmann {
    template <>
    struct adl_serializer<Entity> {
        static void to_json(json& j, const Entity& value) {
            j = json({
                    {"id", value.id},
                    {"modelId", value.modelId},
                    {"scale", value.scale},
                    {"position", value.position},
                    {"rotation", value.rotation}
            });
        }

        static void from_json(const json& j, Entity& value) {
            j.at("id").get_to(value.id);
            j.at("modelId").get_to(value.modelId);
            j.at("scale").get_to(value.scale);
            j.at("position").get_to(value.position);
            j.at("rotation").get_to(value.rotation);
        }
    };
}