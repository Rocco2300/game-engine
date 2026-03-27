#pragma once

#include "json.hpp"

struct AABB {
    float x{};
    float y{};
    float z{};
};

namespace nlohmann {
template <>
struct adl_serializer<AABB> {
    static void to_json(json& j, const AABB& value) {
        j = json({
                {"x", value.x},
                {"y", value.y},
                {"z", value.z},
        });
    }

    static void from_json(const json& j, AABB& value) {
        j.at("x").get_to(value.x);
        j.at("y").get_to(value.y);
        j.at("z").get_to(value.z);
    }
};
}
