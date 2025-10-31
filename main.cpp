#include <GL/gl3w.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <vector>

#include "fps_camera.hpp"
#include "input.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "program.hpp"

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

    Input::init(window);

    Shader vertexShader(Shader::Type::Vertex, "test.vert");
    Shader fragmentShader(Shader::Type::Fragment, "test.frag");
    Program program;
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link();

    Model model("C:\\Users\\grigo\\Repos\\game-engine\\monkey.obj");

    Mesh mesh(vertices, indices);

    FPSCamera camera({0, 0, 3}, 60, 4.f / 3.f);

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
        glClear(GL_COLOR_BUFFER_BIT);

        program.setUniformMat4("mvp", camera.transform());

        program.use();
        model.draw();
        //mesh.draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
