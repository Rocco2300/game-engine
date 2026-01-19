#pragma once

class Event;

class IEventDispatcher {
public:
    virtual ~IEventDispatcher() = default;

    virtual void dispatchEvent(const Event& event) = 0;
};