#pragma once

#include "text.hpp"

#include <functional>

struct Button : public Widget {
    WidgetType type() const override {
        return WidgetType::Button;
    }

    void onEvent(const Event& event) override;

    std::string name;

    Text text;

    glm::vec4 color;
    glm::vec4 defaultColor;
    glm::vec4 hoverColor;

    std::function<void()> callback;

    bool isHovered;
};