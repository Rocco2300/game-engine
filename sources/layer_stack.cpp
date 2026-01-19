#include "layer_stack.hpp"

#include "event.hpp"
#include "renderer.hpp"

void LayerStack::push(ILayer& layer, IRenderer& renderer) {
    layer.onAttach(*this);
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

void LayerStack::onEvent(const Event& event) {
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

void LayerStack::dispatchEvent(const Event& event) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); it++) {
        auto& [layer, _] = *it;
        layer->onEvent(event);
    }
}