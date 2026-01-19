#pragma once

#include "layer.hpp"

#include <memory>

class Widget;
class GUIRenderer;

class Canvas : public ILayer {
public:
    Canvas();

    Widget* root() const;

    void onAttach(const IEventDispatcher& dispatcher) override;
    void onDetach() override;

    void onDraw(const IRenderer& renderer) const override;
    void onUpdate(float deltaTime) override;

    void onEvent(const Event& event) override;

private:
    friend class GUIRenderer;

    Widget* m_root;
    IEventDispatcher const* m_dispatcher;
};