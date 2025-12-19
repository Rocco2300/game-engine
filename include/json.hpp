#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nlohmann {
    template <>
    struct adl_serializer<glm::vec3> {
        static void to_json(json& j, const glm::vec3& value) {
            j = json({
                    {"x", value.x},
                    {"y", value.y},
                    {"z", value.z}
            });
        }

        static void from_json(const json& j, glm::vec3& value) {
            j.at("x").get_to(value.x);
            j.at("y").get_to(value.y);
            j.at("z").get_to(value.z);
        }
    };
}
