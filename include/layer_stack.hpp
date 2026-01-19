#pragma once

#include "layer.hpp"
#include "renderer.hpp"
#include "event_dispatcher.hpp"

#include <vector>
#include <utility>

class LayerStack : public IEventDispatcher {
public:
    LayerStack() = default;

    void push(ILayer& layer, IRenderer& renderer);
    void pop();

    void onDraw() const;
    void onEvent(const Event& event);
    void onUpdate(float deltaTime);

    void dispatchEvent(const Event& event) override;

private:
    std::vector<std::pair<ILayer*, IRenderer*>> m_layers;
};