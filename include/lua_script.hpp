#pragma once

#include "adapter.hpp"
#include "lua_functions.hpp"

#include <concepts>
#include <iostream>
#include <filesystem>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

template <typename T>
concept IsLuaSerializable = requires(lua_State* L, T& t, std::string_view name) {
    { Adapter<T>::index(L) } -> std::same_as<int>;

    { Adapter<T>::newindex(L) } -> std::same_as<int>;

    { Adapter<T>::expose(L, name, t) } -> std::same_as<void>;
};

template <typename T>
requires ((std::floating_point<T> || std::integral<T>) && !std::same_as<T, bool>)
void push_arg(lua_State* L, T v) {
    lua_pushnumber(L, v);
}

inline void push_arg(lua_State* L, bool v) {
    lua_pushboolean(L, v);
}

template <typename T>
requires std::convertible_to<T, std::string_view>
void push_arg(lua_State* L, T v) {
    std::string_view sv = v;
    lua_pushlstring(L, sv.data(), sv.size());
}

class LuaScript {
public:
    LuaScript() = default;
    LuaScript(const std::filesystem::path& path) {
        m_path  = path;
        m_state = luaL_newstate();
        luaL_openlibs(m_state);

        int err = luaL_loadfile(m_state, path.string().c_str());
        if (err) {
            std::cerr << "Error opening script " << path << '\n';

            lua_close(m_state);
            return;
        }

        err = !err && lua_pcall(m_state, 0, 0, 0);
        if (err) {
            std::cerr << "Error compiling script " << path << '\n';

            lua_close(m_state);
            return;
        }

        for (const auto& [name, function] : luaLib) {
            lua_pushcfunction(m_state, function);
            lua_setglobal(m_state, name.c_str());
        }
    }

    //~LuaScript() {
    //    if (!m_state) {
    //        return;
    //    }

    //    lua_close(m_state);
    //}

    const std::filesystem::path& path() const {
        return m_path;
    }

    void load(const std::filesystem::path& path) {
        if (m_state != nullptr) {
            return;
        }

        m_path  = path;
        m_state = luaL_newstate();
        luaL_openlibs(m_state);

        int err = luaL_loadfile(m_state, path.string().c_str());
        if (err) {
            std::cerr << "Error opening script " << path << '\n';

            lua_close(m_state);
            return;
        }

        err = !err && lua_pcall(m_state, 0, 0, 0);
        if (err) {
            std::cerr << "Error compiling script " << path << '\n';

            lua_close(m_state);
            return;
        }

        for (const auto& [name, function] : luaLib) {
            lua_pushcfunction(m_state, function);
            lua_setglobal(m_state, name.c_str());
        }
    }

    template <typename... Args>
    void run(std::string_view function = "", Args&&... args) {
        if (function.empty() && sizeof...(args) > 0) {
            return;
        }

        int type{};
        if (!function.empty()) {
            type = lua_getglobal(m_state, function.data());
        }

        if (type != LUA_TFUNCTION) {
            std::cerr << "Function " << function << " not found\n";

            lua_pop(m_state, 1);
            return;
        }

        (push_arg(m_state, std::forward<Args>(args)), ...);

        if (lua_pcall(m_state, sizeof...(args), 0, 0)) {
            std::cerr << "Error running function " << function << '\n';
        }
    }

    template <typename T>
    void set(std::string_view name, T& value) {
        Adapter<T>::expose(m_state, name, value);
    }

    void set(std::string_view name, lua_CFunction function) {
        lua_pushcfunction(m_state, function);
        lua_setglobal(m_state, name.data());
    }

    bool loaded() {
        return m_state != nullptr;
    }

private:
    lua_State* m_state{};
    std::filesystem::path m_path{};
};