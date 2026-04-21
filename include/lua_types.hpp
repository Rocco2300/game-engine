#pragma once

#include "lua_script.hpp"

#include <glm/glm.hpp>

#include <string_view>

template <>
struct Adapter<glm::vec3> {
    static int index(lua_State* L) {
        glm::vec3** udata = static_cast<glm::vec3**>(luaL_checkudata(L, 1, "Vec3Meta"));
        if (!udata) {
            std::cerr << "error in dereferencing vec3 from lua\n";

            lua_pushnil(L);
            return 1;
        }

        glm::vec3* vec  = *udata;
        std::string key = luaL_checkstring(L, 2);

        if (key == "x") {
            lua_pushnumber(L, vec->x);
        } else if (key == "y") {
            lua_pushnumber(L, vec->y);
        } else if (key == "z") {
            lua_pushnumber(L, vec->z);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    static int newindex(lua_State* L) {
        glm::vec3** udata = static_cast<glm::vec3**>(luaL_checkudata(L, 1, "Vec3Meta"));
        if (!udata) {
            std::cerr << "error in dereferencing vec3 from lua\n";

            lua_pushnil(L);
            return 1;
        }

        glm::vec3* vec = *udata;
        std::string key = luaL_checkstring(L, 2);
        float value = static_cast<float>(luaL_checknumber(L, 3));

        if (key == "x") {
            lua_pushnumber(L, value);
        } else if (key == "y") {
            lua_pushnumber(L, value);
        } else if (key == "z") {
            lua_pushnumber(L, value);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    static void expose(lua_State* L, std::string_view name, glm::vec3& t) {
        luaL_newmetatable(L, "Vec3Meta");

        lua_pushcfunction(L, index);
        lua_setfield(L, -2, "__index");

        lua_pushcfunction(L, newindex);
        lua_setfield(L, -2, "__newindex");

        lua_pop(L, -1);

        glm::vec3** udata = static_cast<glm::vec3**>(lua_newuserdata(L, sizeof(glm::vec3*)));
        *udata = &t;

        luaL_getmetatable(L, "Vec3Meta");
        lua_setmetatable(L, -2);

        lua_setglobal(L, name.data());
    }
};