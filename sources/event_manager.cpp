#include "event_manager.hpp"

#include <glfw/glfw3.h>

#include "input.hpp"

GLFWwindow* EventManager::m_window{};
std::queue<Event> EventManager::m_events{};

void EventManager::init(GLFWwindow* window) {
    m_window = window;

    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, cursorPositionCallback);
}

std::optional<Event> EventManager::pollEvent() {
    if (m_events.empty()) {
        glfwPollEvents();
    }

    std::optional<Event> event;
    if (!m_events.empty()) {
        event.emplace(m_events.front());
        m_events.pop();
    }

    return event;
}

void EventManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input::keyCallback(window, key, scancode, action, mods);

    if (action == GLFW_PRESS) {
        m_events.emplace(Event::KeyPress{key});
    } else if (action == GLFW_RELEASE) {
        m_events.emplace(Event::KeyRelease{key});
    }
}

void EventManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Input::mouseButtonCallback(window, button, action, mods);

    if (action == GLFW_PRESS) {
        m_events.emplace(Event::MouseButtonPress{button});
    } else if (action == GLFW_RELEASE) {
        m_events.emplace(Event::MouseButtonRelease{button});
    }
}

void EventManager::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    Input::cursorPositionCallback(window, xpos, ypos);

    m_events.emplace(Event::MouseMove{xpos, ypos});
}
