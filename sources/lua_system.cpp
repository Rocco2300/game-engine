#include "lua_system.hpp"

#include "entity.hpp"
#include "lua_types.hpp"
#include "lua_script.hpp"

void LuaSystem::onRegister(std::vector<Entity>& entities) {
    m_entities = &entities;
}

void LuaSystem::onAttach() {
    for (auto& entity : *m_entities) {
        if (!entity.luaScript.loaded()) {
            continue;
        }

        entity.luaScript.run("onAttach");
    }
}

void LuaSystem::onDetach() {
    for (auto& entity : *m_entities) {
        if (!entity.luaScript.loaded()) {
            continue;
        }

        entity.luaScript.run("onDetach");
    }
}

void LuaSystem::onUpdate(float deltaTime) {
    for (auto& entity : *m_entities) {
        if (!entity.luaScript.loaded()) {
            continue;
        }

        entity.luaScript.run("onUpdate", deltaTime);
    }
}
