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
    void onEvent(int event);
    void onUpdate(float deltaTime);

    void dispatchEvent(int event) override;

private:
    std::vector<std::pair<ILayer*, IRenderer*>> m_layers;
};