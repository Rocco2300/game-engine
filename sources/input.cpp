#include "input.hpp"

#include <glfw/glfw3.h>

GLFWwindow* Input::m_window;

bool Input::m_bindCursor;
glm::vec2 Input::m_cursorDelta;
glm::vec2 Input::m_cursorPosition;

std::unordered_map<int, bool> Input::m_currentKeys;
std::unordered_map<int, bool> Input::m_previousKeys;

std::unordered_map<int, bool> Input::m_currentButtons;
std::unordered_map<int, bool> Input::m_previousButtons;

void Input::update() {
    m_previousKeys    = m_currentKeys;
    m_previousButtons = m_currentButtons;
}

// clang-format off
bool Input::keyHeld(int key) {
    return m_currentKeys[key];
}

bool Input::keyPressed(int key) {
    return m_currentKeys[key] && !m_previousKeys[key];
}

bool Input::keyReleased(int key) {
    return !m_currentKeys[key] && m_previousKeys[key];
}

bool Input::mouseButtonHeld(int button) {
    return m_currentButtons[button];
}

bool Input::mouseButtonPressed(int button) {
    return m_currentButtons[button] && !m_previousButtons[button];
}

bool Input::mouseButtonReleased(int button) {
    return !m_currentButtons[button] && m_previousButtons[button];
}

glm::vec2 Input::cursorDelta() {
    return m_cursorDelta;
}

glm::vec2 Input::cursorPosition() {
    return m_cursorPosition;
}

void Input::hideCursor(bool value) {
    if (value) {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    } else {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Input::bindCursor(bool value) {
    m_bindCursor = value;
}
// clang-format off

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_currentKeys[key] = true;
    } else if (action == GLFW_RELEASE) {
        m_currentKeys[key] = false;
    }
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_currentButtons[button] = true;
    } else if (action == GLFW_RELEASE) {
        m_currentButtons[button] = false;
    }
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    m_cursorPosition.x = xpos;
    m_cursorPosition.y = ypos;

    m_cursorDelta = glm::vec2(0);
    if (m_bindCursor) {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);

        glm::vec2 windowCenter(width / 2.0, height / 2.0);
        m_cursorDelta = m_cursorPosition - windowCenter;

        glfwSetCursorPos(m_window, windowCenter.x, windowCenter.y);
    }
}