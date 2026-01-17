#pragma once

#include "widget.hpp"

struct Frame : public Widget {
public:
    WidgetType type() const override {
        return WidgetType::Frame;
    }

    glm::vec4 color;
};