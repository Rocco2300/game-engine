#pragma once

class Renderer;

class ILayer {
public:
    virtual ~ILayer() = 0;

    virtual void onAttach() = 0;
    virtual void onDetach() = 0;

    virtual void onDraw(Renderer& renderer) = 0;
    virtual void onUpdate(float deltaTime) = 0;

    virtual void onEvent(int event) = 0;
};