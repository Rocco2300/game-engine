#include <GL/gl3w.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <vector>

#include "mesh.hpp"
#include "model.hpp"
#include "program.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::vector<Vertex> vertices = {
        {{0.5f,  0.5f, 0.0f}, {0.f, 0.f, 1.0f}, {1.f, 1.f}},   // top right
        {{0.5f,  -0.5f, 0.0f}, {0.f, 0.f, 1.0f}, {1.f, 0.f}},   // bottom right
        {{-0.5f,  -0.5f, 0.0f}, {0.f, 0.f, 1.0f}, {0.f, 0.f}},   // bottom left
        {{-0.5f,  0.5f, 0.0f}, {0.f, 0.f, 1.0f}, {0.f, 1.f}},   // top left
};

std::vector<uint32_t> indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }

    Shader vertexShader(Shader::Type::Vertex, "test.vert");
    Shader fragmentShader(Shader::Type::Fragment, "test.frag");
    Program program;
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.link();

    Model model("C:\\Users\\grigo\\Repos\\game-engine\\monkey.obj");

    Mesh mesh(vertices, indices);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        model.draw();
        //mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
