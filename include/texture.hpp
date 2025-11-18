#pragma once

#include "asset_store.hpp"

#include <string>
#include <cstdint>

class Texture {
public:
    enum class Type {
        Diffuse,
        Normal,
        Specular,
    };

private:
    Type m_type;
    uint32_t m_id;

private:
    Texture() = default;
    Texture(const std::string& path, Type type);

public:
    void bind() const;

private:
    int getBindUnit() const;
    int getFormat(int channelNumber);
    int getInternalFormat(int channelNumber);

private:
    friend class Program;
    friend class AssetStore<Texture>;
};