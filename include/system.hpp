#pragma once

#include <vector>

struct Entity;

class ISystem {
public:
    ISystem() = default;

    virtual void onRegister(std::vector<Entity>&) = 0;

    virtual void onAttach() = 0;
    virtual void onDetach() = 0;

    virtual void onUpdate(float deltaTime) = 0;

    virtual ~ISystem() = default;
};