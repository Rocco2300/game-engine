#pragma once

class IEventDispatcher {
public:
    virtual void dispatchEvent(int event) = 0;
};