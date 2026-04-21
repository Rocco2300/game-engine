#pragma once

#include "input.hpp"

#include <array>
#include <string>
#include <utility>
#include <unordered_map>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#pragma region GLFW_KEYS

#ifndef GLFW_KEYS_H
#define GLFW_KEYS_H

/* Printable keys */
#define GLFW_KEY_SPACE           32
#define GLFW_KEY_APOSTROPHE      39  /* ' */
#define GLFW_KEY_COMMA           44  /* , */
#define GLFW_KEY_MINUS           45  /* - */
#define GLFW_KEY_PERIOD          46  /* . */
#define GLFW_KEY_SLASH           47  /* / */
#define GLFW_KEY_0               48
#define GLFW_KEY_1               49
#define GLFW_KEY_2               50
#define GLFW_KEY_3               51
#define GLFW_KEY_4               52
#define GLFW_KEY_5               53
#define GLFW_KEY_6               54
#define GLFW_KEY_7               55
#define GLFW_KEY_8               56
#define GLFW_KEY_9               57
#define GLFW_KEY_SEMICOLON       59  /* ; */
#define GLFW_KEY_EQUAL           61  /* = */
#define GLFW_KEY_A               65
#define GLFW_KEY_B               66
#define GLFW_KEY_C               67
#define GLFW_KEY_D               68
#define GLFW_KEY_E               69
#define GLFW_KEY_F               70
#define GLFW_KEY_G               71
#define GLFW_KEY_H               72
#define GLFW_KEY_I               73
#define GLFW_KEY_J               74
#define GLFW_KEY_K               75
#define GLFW_KEY_L               76
#define GLFW_KEY_M               77
#define GLFW_KEY_N               78
#define GLFW_KEY_O               79
#define GLFW_KEY_P               80
#define GLFW_KEY_Q               81
#define GLFW_KEY_R               82
#define GLFW_KEY_S               83
#define GLFW_KEY_T               84
#define GLFW_KEY_U               85
#define GLFW_KEY_V               86
#define GLFW_KEY_W               87
#define GLFW_KEY_X               88
#define GLFW_KEY_Y               89
#define GLFW_KEY_Z               90
#define GLFW_KEY_LEFT_BRACKET    91  /* [ */
#define GLFW_KEY_BACKSLASH       92  /* \ */
#define GLFW_KEY_RIGHT_BRACKET   93  /* ] */
#define GLFW_KEY_GRAVE_ACCENT    96  /* ` */
#define GLFW_KEY_WORLD_1         161 /* non-US #1 */
#define GLFW_KEY_WORLD_2         162 /* non-US #2 */

/* Function keys */
#define GLFW_KEY_ESCAPE          256
#define GLFW_KEY_ENTER           257
#define GLFW_KEY_TAB             258
#define GLFW_KEY_BACKSPACE       259
#define GLFW_KEY_INSERT          260
#define GLFW_KEY_DELETE          261
#define GLFW_KEY_RIGHT           262
#define GLFW_KEY_LEFT            263
#define GLFW_KEY_DOWN            264
#define GLFW_KEY_UP              265
#define GLFW_KEY_PAGE_UP         266
#define GLFW_KEY_PAGE_DOWN       267
#define GLFW_KEY_HOME            268
#define GLFW_KEY_END             269
#define GLFW_KEY_CAPS_LOCK       280
#define GLFW_KEY_SCROLL_LOCK     281
#define GLFW_KEY_NUM_LOCK        282
#define GLFW_KEY_PRINT_SCREEN    283
#define GLFW_KEY_PAUSE           284
#define GLFW_KEY_F1              290
#define GLFW_KEY_F2              291
#define GLFW_KEY_F3              292
#define GLFW_KEY_F4              293
#define GLFW_KEY_F5              294
#define GLFW_KEY_F6              295
#define GLFW_KEY_F7              296
#define GLFW_KEY_F8              297
#define GLFW_KEY_F9              298
#define GLFW_KEY_F10             299
#define GLFW_KEY_F11             300
#define GLFW_KEY_F12             301
#define GLFW_KEY_F13             302
#define GLFW_KEY_F14             303
#define GLFW_KEY_F15             304
#define GLFW_KEY_F16             305
#define GLFW_KEY_F17             306
#define GLFW_KEY_F18             307
#define GLFW_KEY_F19             308
#define GLFW_KEY_F20             309
#define GLFW_KEY_F21             310
#define GLFW_KEY_F22             311
#define GLFW_KEY_F23             312

#define GLFW_KEY_RIGHT_SHIFT     344
#define GLFW_KEY_RIGHT_CONTROL   345
#define GLFW_KEY_RIGHT_ALT       346
#define GLFW_KEY_RIGHT_SUPER     347

/* Modifier keys */
#define GLFW_KEY_LEFT_SHIFT      340
#define GLFW_KEY_LEFT_CONTROL    341
#define GLFW_KEY_LEFT_ALT        342
#define GLFW_KEY_LEFT_SUPER      343 /* Windows Key / Command Key */

#endif

#pragma endregion

static int getKey(lua_State* L) {
    std::string key = luaL_checkstring(L, 1);

    static const std::unordered_map<std::string, int> keyMap = {
        // Alphanumeric
        {"a", GLFW_KEY_A}, {"b", GLFW_KEY_B}, {"c", GLFW_KEY_C}, {"d", GLFW_KEY_D},
        {"e", GLFW_KEY_E}, {"f", GLFW_KEY_F}, {"g", GLFW_KEY_G}, {"h", GLFW_KEY_H},
        {"i", GLFW_KEY_I}, {"j", GLFW_KEY_J}, {"k", GLFW_KEY_K}, {"l", GLFW_KEY_L},
        {"m", GLFW_KEY_M}, {"n", GLFW_KEY_N}, {"o", GLFW_KEY_O}, {"p", GLFW_KEY_P},
        {"q", GLFW_KEY_Q}, {"r", GLFW_KEY_R}, {"s", GLFW_KEY_S}, {"t", GLFW_KEY_T},
        {"u", GLFW_KEY_U}, {"v", GLFW_KEY_V}, {"w", GLFW_KEY_W}, {"x", GLFW_KEY_X},
        {"y", GLFW_KEY_Y}, {"z", GLFW_KEY_Z},
        {"0", GLFW_KEY_0}, {"1", GLFW_KEY_1}, {"2", GLFW_KEY_2}, {"3", GLFW_KEY_3},
        {"4", GLFW_KEY_4}, {"5", GLFW_KEY_5}, {"6", GLFW_KEY_6}, {"7", GLFW_KEY_7},
        {"8", GLFW_KEY_8}, {"9", GLFW_KEY_9},

        // Special Keys
        {"space",    GLFW_KEY_SPACE},
        {"escape",   GLFW_KEY_ESCAPE},
        {"enter",    GLFW_KEY_ENTER},
        {"tab",      GLFW_KEY_TAB},
        {"shift",    GLFW_KEY_LEFT_SHIFT},
        {"ctrl",     GLFW_KEY_LEFT_CONTROL},
        {"alt",      GLFW_KEY_LEFT_ALT},
        {"up",       GLFW_KEY_UP},
        {"down",     GLFW_KEY_DOWN},
        {"left",     GLFW_KEY_LEFT},
        {"right",    GLFW_KEY_RIGHT}
    };

    int intKey  = keyMap.at(key);
    bool ret    = Input::keyHeld(intKey);

    lua_pushboolean(L, ret);

    return 1;
}

static int isLeftMouseHeld(lua_State* L) {
    bool ret = Input::mouseButtonHeld(1);

    lua_pushboolean(L, ret);

    return 1;
}

struct LuaFunction {
    std::string name;
    lua_CFunction func;
};

static constexpr LuaFunction luaLib[] = {
    {"getKey", getKey},
    {"isLeftMouseHeld", isLeftMouseHeld}
};
