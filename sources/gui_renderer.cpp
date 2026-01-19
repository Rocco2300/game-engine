#include "gui_renderer.hpp"

#include "button.hpp"
#include "canvas.hpp"
#include "frame.hpp"
#include "label.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "widget.hpp"

#include <GL/gl3w.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

GUIRenderer::GUIRenderer()
    : IRenderer("C:/Users/grigo/Repos/game-engine/shaders", "gui") {

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Error initializing free type!\n";
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face)) {
        std::cerr << "Error loading font!\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "Error loading glyph\n";
            continue;
        }

        TextureData textureData = {
                .width  = face->glyph->bitmap.width,
                .height = face->glyph->bitmap.rows,
                .data   = face->glyph->bitmap.buffer,
                .format = TextureFormat::RED
        };

        Texture texture(textureData);
        Character character = {
                texture,
                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                static_cast<uint32_t>(face->glyph->advance.x),
        };

        m_characters.emplace(c, character);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    m_program.setUniformMat4("projection", m_projection);
}

void GUIRenderer::draw(const IDrawable& drawable) const {
    const auto& canvas = dynamic_cast<const Canvas&>(drawable);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_program.use();

    glBindVertexArray(m_vao);

    drawImpl(*canvas.m_root);

    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void GUIRenderer::drawImpl(const Text& text, glm::vec2 parentPosition) const {
    m_program.setUniformVec4("color", text.color);
    m_program.setUniformBool("isCharacter", true);

    float x = parentPosition.x + text.position.x;
    float y = parentPosition.y + text.position.y;
    for (char c: text.content) {
        auto ch = m_characters.at(c);

        float xpos = x + ch.bearing.x;
        float ypos = y - (ch.size.y - ch.bearing.y);

        float w = ch.size.x;
        float h = ch.size.y;

        float vertices[6][4] = {
                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos, ypos, 0.0f, 1.0f},
                {xpos + w, ypos, 1.0f, 1.0f},

                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos + w, ypos, 1.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 0.0f}
        };

        ch.texture.bind(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6);
    }
}

void GUIRenderer::drawImpl(const Frame& frame, glm::vec2 parentPosition) const {
    m_program.setUniformVec4("color", frame.color);
    m_program.setUniformBool("isCharacter", false);

    float xpos = parentPosition.x + frame.position.x;
    float ypos = parentPosition.y + frame.position.y;

    float w = frame.size.x;
    float h = frame.size.y;

    float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GUIRenderer::drawImpl(const Label& label, glm::vec2 parentPosition) const {
    m_program.setUniformVec4("color", label.color);
    m_program.setUniformBool("isCharacter", false);

    float xpos = parentPosition.x + label.position.x;
    float ypos = parentPosition.y + label.position.y;

    float w = label.size.x;
    float h = label.size.y;

    float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    drawImpl(label.text, label.position);
}

void GUIRenderer::drawImpl(const Button& button, glm::vec2 parentPosition) const {
    m_program.setUniformVec4("color", button.color);
    m_program.setUniformBool("isCharacter", false);

    float xpos = parentPosition.x + button.position.x;
    float ypos = parentPosition.y + button.position.y;

    float w = button.size.x;
    float h = button.size.y;

    float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    drawImpl(button.text, button.position);
}

void GUIRenderer::drawImpl(const Widget& widget, glm::vec2 parentPosition) const {
    auto type = widget.type();
    switch (type) {
        using enum WidgetType;
    case Frame:
        drawImpl(dynamic_cast<const struct Frame&>(widget), parentPosition);
        break;
    case Text:
        drawImpl(dynamic_cast<const struct Text&>(widget), parentPosition);
        break;
    case Label:
        drawImpl(dynamic_cast<const struct Label&>(widget), parentPosition);
        break;
    case Button:
        drawImpl(dynamic_cast<const struct Button&>(widget), parentPosition);
        break;
    }

    for (const auto& child: widget.children) {
        drawImpl(*child, widget.position);
    }
}