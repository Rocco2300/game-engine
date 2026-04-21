#pragma once

#include "system.hpp"

class LuaSystem : public ISystem {
public:
    LuaSystem() = default;

    void onRegister(std::vector<Entity>& entities) override;

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float deltaTime) override;

    ~LuaSystem() override = default;

private:
    std::vector<Entity>* m_entities ;
};