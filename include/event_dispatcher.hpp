#pragma once

class IEventDispatcher {
public:
    virtual ~IEventDispatcher() = 0;

    virtual void dispatchEvent(int event) = 0;
};