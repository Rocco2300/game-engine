#pragma once

#include <queue>
#include <optional>

#include "event.hpp"

class Event;
class GLFWwindow;

class EventManager {
public:
    EventManager() = delete;
    static void init(GLFWwindow* window);

    static std::optional<Event> pollEvent();

    static void postEvent(const Event& event);

private:
    static GLFWwindow* m_window;
    static std::queue<Event> m_events;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};

