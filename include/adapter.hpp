#pragma once

class lua_State;

template <typename T>
struct Adapter {
    static int index(lua_State* L) { return 0; }

    static int newindex(lua_State* L) { return 0; }

    static void expose(lua_State* L, T& t) {}
};