#pragma once

#include <string>
#include <filesystem>

enum class TextureFormat {
    RED,
    RGB,
    RGBA
};

struct TextureData {
    uint32_t width;
    uint32_t height;
    uint8_t* data;

    TextureFormat format;
};

TextureFormat toTextureFormat(int channelNumber);

class Texture {
public:
    Texture() = default;
    Texture(const TextureData& textureData);

    void bind(uint32_t unit) const;

protected:
    void setupTexture(const TextureData& textureData);

    uint32_t m_id{};

    uint32_t m_width{};
    uint32_t m_height{};
};