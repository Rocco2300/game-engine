#include "canvas.hpp"

#include "text.hpp"
#include "frame.hpp"
#include "widget.hpp"
#include "gui_renderer.hpp"

Canvas::Canvas() {
    m_root = new Frame();

    auto* frame = dynamic_cast<Frame*>(m_root);
    frame->size = {800.f, 600.f};
    frame->position = {0.0f, 0.0f};
    frame->color = {0.6f, 0.1f, 0.2f, 0.0f};

    /*
    m_root = new Text();

    auto* text = dynamic_cast<Text*>(m_root);
    text->position = {10, 20};
    text->color = {1, 1, 1, 1};
    text->text = "This is text";
    */
}

Widget* Canvas::root() const {
    return m_root;
}

void Canvas::onAttach() {

}

void Canvas::onDetach() {

}

void Canvas::onDraw(const IRenderer& renderer) const {
    renderer.draw(*this);
}

void Canvas::onUpdate(float deltaTime) {

}

void Canvas::onEvent(int event) {
    m_root->onEvent(event);
}

