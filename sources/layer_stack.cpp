#include "layer_stack.hpp"

#include "renderer.hpp"

void LayerStack::push(ILayer& layer) {
    layer.onAttach();
    m_layers.push_back(&layer);
}

void LayerStack::pop() {
    m_layers.back()->onDetach();
    m_layers.pop_back();
}

void LayerStack::onDraw(Renderer& renderer) {
    for (auto it = m_layers.begin(); it != m_layers.end(); it++) {
        auto& layer = *it;
        layer->onDraw(renderer);
    }
}

void LayerStack::onUpdate(float deltaTime) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& layer = *it;
        layer->onUpdate(deltaTime);
    }
}

void LayerStack::dispatchEvent(int event) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& layer = *it;
        layer->onEvent(event);
    }
}