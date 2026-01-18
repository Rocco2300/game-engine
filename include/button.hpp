#pragma once

#include "text.hpp"

#include <functional>

struct Button : public Widget {
    WidgetType type() const override {
        return WidgetType::Button;
    }

    void onEvent(int event) override {
        if (event == 2) {
            callback();
        }

        Widget::onEvent(event);
    }

    Text text;
    glm::vec4 color;
    glm::vec4 defaultColor;
    glm::vec4 hoverColor;
    std::function<void()> callback;
};