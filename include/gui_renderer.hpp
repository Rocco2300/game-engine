#pragma once

#include "camera.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "renderer.hpp"

class GUIRenderer : public IRenderer<std::string> {
public:
    GUIRenderer();

    void draw(const std::string& drawable) override;

private:
    struct Character {
        Texture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
    };

    uint32_t m_vao;
    uint32_t m_vbo;

    glm::mat4 m_projection{};
    std::unordered_map<char, Character> m_characters;
};