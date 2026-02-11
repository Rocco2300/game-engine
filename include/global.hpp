#pragma once

#include <filesystem>

struct Global {
    std::filesystem::path assetsPath;
    std::filesystem::path shadersPath;
    std::filesystem::path projectPath;
};

extern Global global;