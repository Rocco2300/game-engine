#pragma once

#include "event.hpp"

#include <glm/glm.hpp>

#include <memory>

class GUIRenderer;

enum class WidgetType {
    Frame,
    Text,
    Label,
    Button,
    Canvas
};

struct Widget {
public:
    virtual ~Widget() = default;

    virtual WidgetType type() const = 0;

    virtual void onEvent(const Event& event) {
        for (const auto& child : children) {
            child->onEvent(event);
        }
    }

    virtual void insertChild(Widget* widget) {
        children.push_back(widget);
    }

    glm::vec2 size{};
    glm::vec2 position{};

    std::vector<Widget*> children{};
};