#pragma once

#include "asset_store.hpp"

#include <span>
#include <string>
#include <cstdint>

class Texture {
public:
    enum class Type {
        Diffuse,
        Normal,
        Specular,
    };

    void bind() const;

private:
    friend class Program;
    friend class AssetStore<Texture>;

    Type m_type;
    uint32_t m_id;

    Texture() = default;
    Texture(const std::string& path, Type type);
    Texture(const uint8_t* data, int width, int height, int channelNumber, Type type);

    int getBindUnit() const;
    int getFormat(int channelNumber);
    int getInternalFormat(int channelNumber);
    void setupTexture(const uint8_t* data, int width, int height, int channelNumber);
};