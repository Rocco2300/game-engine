#pragma once

#include "layer.hpp"

#include <memory>

class Widget;
class GUIRenderer;

class Canvas : public ILayer {
public:
    Canvas();

    Widget* root() const;

    void onAttach() override;
    void onDetach() override;

    void onDraw(const IRenderer& renderer) const override;
    void onUpdate(float deltaTime) override;

    void onEvent(int event) override;

private:
    friend class GUIRenderer;

    Widget* m_root;
};