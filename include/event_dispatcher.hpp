#pragma once

class IEventDispatcher {
public:
    virtual ~IEventDispatcher() = default;

    virtual void dispatchEvent(int event) = 0;
};