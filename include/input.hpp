#pragma once

#include <unordered_map>

class GLFWwindow;

class Input {
private:
    static std::unordered_map<int, bool> m_currentKeys;
    static std::unordered_map<int, bool> m_previousKeys;

public:
    Input() = delete;
    static void init(GLFWwindow* window);
    static void update();

    static bool keyHeld(int key);
    static bool keyPressed(int key);
    static bool keyReleased(int key);

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};