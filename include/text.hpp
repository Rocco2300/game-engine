#pragma once

#include "widget.hpp"

struct Text : public Widget {
    WidgetType type() const override {
        return WidgetType::Text;
    }

    glm::vec4 color;
    std::string text;
};