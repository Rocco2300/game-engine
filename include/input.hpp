#pragma once

#include <glm/vec2.hpp>

#include <unordered_map>

class GLFWwindow;
class Input {
public:
    Input() = delete;
    static void init(GLFWwindow* window);
    static void update();

    static bool keyHeld(int key);
    static bool keyPressed(int key);
    static bool keyReleased(int key);

    static bool mouseButtonHeld(int button);
    static bool mouseButtonPressed(int button);
    static bool mouseButtonReleased(int button);

    static glm::vec2 cursorDelta();
    static glm::vec2 cursorPosition();
    static void hideCursor(bool value);
    static void bindCursor(bool value);

private:
    friend class EventManager;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    static GLFWwindow* m_window;

    static bool m_bindCursor;
    static glm::vec2 m_cursorDelta;
    static glm::vec2 m_cursorPosition;

    static std::unordered_map<int, bool> m_currentKeys;
    static std::unordered_map<int, bool> m_previousKeys;

    static std::unordered_map<int, bool> m_currentButtons;
    static std::unordered_map<int, bool> m_previousButtons;
};