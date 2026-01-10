#pragma once

#include "layer.hpp"
#include "event_dispatcher.hpp"

#include <vector>

class LayerStack : public IEventDispatcher {
public:
    LayerStack() = default;

    void push(ILayer& layer);
    void pop();

    void onDraw(Renderer& renderer);
    void onUpdate(float deltaTime);

    void dispatchEvent(int event) override;

private:
    std::vector<ILayer*> m_layers;
};