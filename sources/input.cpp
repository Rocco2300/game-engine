#include "input.hpp"

#include <glfw/glfw3.h>

std::unordered_map<int, bool> Input::m_currentKeys;
std::unordered_map<int, bool> Input::m_previousKeys;

void Input::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
}

void Input::update() {
    m_previousKeys = m_currentKeys;
}

bool Input::keyHeld(int key) {
    return m_currentKeys[key];
}

bool Input::keyPressed(int key) {
    return m_currentKeys[key] && !m_previousKeys[key];
}

bool Input::keyReleased(int key) {
    return !m_currentKeys[key] && m_previousKeys[key];
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_currentKeys[key] = true;
    } else if (action == GLFW_RELEASE) {
        m_currentKeys[key] = false;
    }
}