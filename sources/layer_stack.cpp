#include "layer_stack.hpp"

#include "renderer.hpp"

void LayerStack::push(ILayer& layer, IRenderer& renderer) {
    layer.onAttach();
    m_layers.push_back({&layer, &renderer});
}

void LayerStack::pop() {
    m_layers.back().first->onDetach();
    m_layers.pop_back();
}

void LayerStack::onDraw() const {
    for (auto it = m_layers.begin(); it != m_layers.end(); it++) {
        auto& [layer, renderer] = *it;
        layer->onDraw(*renderer);
    }
}

void LayerStack::onEvent(int event) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& [layer, _] = *it;
        layer->onEvent(event);
    }
}

void LayerStack::onUpdate(float deltaTime) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& [layer, _] = *it;
        layer->onUpdate(deltaTime);
    }
}

void LayerStack::dispatchEvent(int event) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& [layer, _] = *it;
        layer->onEvent(event);
    }
}