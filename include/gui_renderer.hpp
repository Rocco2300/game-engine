#pragma once

#include "camera.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "renderer.hpp"

class Text;
class Frame;
class Widget;

class GUIRenderer : public IRenderer {
public:
    GUIRenderer();

    void draw(const IDrawable& drawable) const override;

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

    void drawImpl(const Text& text) const;
    void drawImpl(const Frame& frame) const;
    void drawImpl(const Widget& widget) const;
};