#include "button.hpp"

#include "event_manager.hpp"

#include <glfw/glfw3.h>

static bool inBounds(glm::vec2 pos, glm::vec2 corner, glm::vec2 size) {
    // pos.x >= corner.x && pos.x <= corner.x + size.x
    // pos.y >= corner.y && pos.y <= corner.y + size.y
    auto verticalInBounds   = pos.x >= corner.x && pos.x <= corner.x + size.x;
    auto horizontalInBounds = pos.y >= corner.y && pos.y <= corner.y + size.y;

    return verticalInBounds && horizontalInBounds;
}

void Button::onEvent(const Event& event) {
    if (event.is<Event::MouseMove>()) {
        auto data = event.get<Event::MouseMove>();

        auto mousePos = glm::vec2{data.xpos, data.ypos};
        isHovered     = inBounds(mousePos, position, size);
        color         = (isHovered) ? defaultColor : hoverColor;
    }

    if (event.is<Event::MouseButtonPress>()) {
        auto data = event.get<Event::MouseButtonPress>();

        if (data.mouseButton == GLFW_MOUSE_BUTTON_LEFT && isHovered) {
            callback();
            EventManager::postEvent(Event::ButtonPress{name});
        }
    }

    Widget::onEvent(event);
}