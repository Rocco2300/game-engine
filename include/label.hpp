#pragma once

#include "text.hpp"

struct Label : public Widget {
    WidgetType type() const override {
        return WidgetType::Label;
    }

    Text text;
    glm::vec4 color;
};