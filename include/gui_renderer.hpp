#pragma once

#include "camera.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "renderer.hpp"

struct Text;
struct Frame;
struct Label;
struct Widget;

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

    void drawImpl(const Text& text, glm::vec2 parentPosition = {0, 0}) const;
    void drawImpl(const Frame& frame, glm::vec2 parentPosition = {0, 0}) const;
    void drawImpl(const Label& label, glm::vec2 parentPosition = {0, 0}) const;
    void drawImpl(const Widget& widget, glm::vec2 parentPosition = {0, 0}) const;
};