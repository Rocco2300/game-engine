#include <GL/gl3w.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "fps_camera.hpp"
#include "input.hpp"
#include "light.hpp"
#include "program.hpp"
#include "renderer.hpp"
#include "asset_manager.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

const unsigned int ScreenWidth = 800;
const unsigned int ScreenHeight = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Game Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    Input::init(window);

    Shader vertexShader(Shader::Type::Vertex, "test.vert");
    Shader fragmentShader(Shader::Type::Fragment, "test.frag");
    Program program;
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link();

    AssetManager::setPath("C:/Users/grigo/Repos/game-engine");

    auto id = AssetManager::loadModel("second_monkey.obj");
    auto model = AssetManager::getModel(id);

    FPSCamera camera({0, 0, 3}, 60, 4.f / 3.f);

    auto direction = glm::vec3(-1);
    Light light(Light::Type::Directional, glm::normalize(direction), glm::normalize(direction));

    Renderer renderer(program, camera, light);

    float deltaTime{};
    float previousFrame{};
    while (!glfwWindowShouldClose(window)) {
        Input::update();
        glfwPollEvents();
        if (Input::keyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        float currentFrame = glfwGetTime();
        deltaTime          = currentFrame - previousFrame;
        previousFrame      = currentFrame;

        camera.update(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.draw(*model);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
