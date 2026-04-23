#pragma once

#include "system.hpp"

class PhysicsSystem : public ISystem {
public:
    void onRegister(std::vector<Entity>&) override;

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float deltaTime) override;

private:
    std::vector<Entity>* m_entities;
};