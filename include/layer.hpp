#pragma once

#include "drawable.hpp"

class Event;
class IEventDispatcher;

class ILayer : public IDrawable {
public:
    virtual ~ILayer() = default;

    virtual void onAttach(const IEventDispatcher& dispatcher) = 0;
    virtual void onDetach() = 0;

    //virtual void onDraw(const & renderer) = 0;
    virtual void onUpdate(float deltaTime) = 0;

    virtual void onEvent(const Event& event) = 0;
};