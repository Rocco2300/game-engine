#include <GL/gl3w.h>
#include <glfw/glfw3.h>

#include <fstream>
#include <iostream>

#include "text.hpp"
#include "label.hpp"
#include "input.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "fps_camera.hpp"
#include "serializer.hpp"
#include "layer_stack.hpp"
#include "gui_renderer.hpp"
#include "asset_manager.hpp"
#include "event_manager.hpp"
#include "scene_renderer.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

const unsigned int ScreenWidth = 800;
const unsigned int ScreenHeight = 600;

int main(int argc, char** argv) {
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
    EventManager::init(window);

    AssetManager::setPath("C:/Users/grigo/Repos/game-engine");
    Serializer::setPath("C:/Users/grigo/Repos/game-engine");

    std::string mode{};
    if (argc > 1) {
        mode = argv[1];
    }

    Scene scene;
    if (mode == "--load") {
        Serializer::loadSceneFile("scene.json");
        Serializer::deserializeAssets();
        Serializer::deserializeScene(scene);
    } else {
        auto id = AssetManager::loadModel("second_monkey.obj");
        auto model = AssetManager::getModel(id);

        auto rootEntityId = scene.addEntity();
        auto* rootEntity  = scene.getEntity(rootEntityId);
        rootEntity->position = glm::vec3(2.f, 0.f, 1.f);

        auto entityId = scene.addEntity(rootEntityId);
        auto* entity = scene.getEntity(entityId);
        entity->modelId = id;

        AssetManager::loadMaterialTexture("pumpkin.jpg", MaterialTexture::Type::Diffuse);
        Serializer::serializeScene(scene);
    }

    Canvas canvas;
    auto* root = canvas.root();

    Label* label = new Label();
    label->color = {0.2f, 0.05f, 0.6f, 1.0f};
    label->size = {320, 100};
    label->position = {10, 20};
    label->text.color = {1, 1, 1, 1,};
    label->text.content = "This is a label";
    label->text.position = {10, 10};

    Text* text = new Text();
    text->position = {10, 500};
    text->color = {1, 1, 1, 1};
    text->content = "This is text";

    Button* button = new Button();
    button->size = {360, 100};
    button->position = {10, 120};
    button->color = {0.5f, 0.08f, 0.15f, 1};
    button->text.content = "This is a button";
    button->text.color = {1, 1, 1, 1};
    button->text.position = {10, 10};
    button->callback = []() {
        std::cout << "Pressed the button\n";
    };
    root->children.push_back(text);
    root->children.push_back(label);
    root->children.push_back(button);

    FPSCamera camera({0, 0, 3}, 60, 4.f / 3.f);

    auto direction = glm::vec3(-1);
    Light light(Light::Type::Directional, glm::normalize(direction), glm::normalize(direction));

    GUIRenderer guiRenderer;
    SceneRenderer renderer(camera, light);

    LayerStack layerStack;
    layerStack.push(scene, renderer);
    layerStack.push(canvas, guiRenderer);

    float deltaTime{};
    float previousFrame{};
    while (!glfwWindowShouldClose(window)) {
        Input::update();

        while (const auto event = EventManager::pollEvent()) {
            if (event->is<Event::KeyPress>()) {
                auto eventData = event->get<Event::KeyPress>();

                if (eventData.keycode == GLFW_KEY_L) {
                    std::cout << "We made it mom!\n";
                }
            }
        }

        if (Input::keyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        if (Input::keyPressed(GLFW_KEY_M)) {
            layerStack.onEvent(2);
        }

        float currentFrame = glfwGetTime();
        deltaTime          = currentFrame - previousFrame;
        previousFrame      = currentFrame;

        camera.update(deltaTime);
        layerStack.onUpdate(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //renderer.draw(scene);
        layerStack.onDraw();

        //guiRenderer.draw("this is a test");

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
