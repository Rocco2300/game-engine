#include "texture.hpp"

#include <GL/gl3w.h>

TextureFormat toTextureFormat(int channelNumber) {
    using enum TextureFormat;

    switch (channelNumber) {
    case 1:
        return RED;
    case 3:
        return RGB;
    case 4:
        return RGBA;
    }

    return RGBA;
}

static uint32_t getFormat(TextureFormat textureFormat) {
    switch (textureFormat) {
        using enum TextureFormat;
    case RED:
        return GL_RED;
    case RGB:
        return GL_RGB;
    case RGBA:
        return GL_RGBA;
    }

    return GL_RGBA;
}

static uint32_t getInternalFormat(TextureFormat textureFormat) {
    switch (textureFormat) {
        using enum TextureFormat;
    case RED:
        return GL_R8;
    case RGB:
        return GL_RGB8;
    case RGBA:
        return GL_RGBA8;
    }

    return GL_RGBA8;
}

Texture::Texture(const TextureData& textureData) {
    setupTexture(textureData);
}

void Texture::bind(uint32_t unit) const {
    glBindTextureUnit(unit, m_id);
}

void Texture::setupTexture(const TextureData& textureData) {
    m_width  = textureData.width;
    m_height = textureData.height;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto format         = getFormat(textureData.format);
    auto internalFormat = getInternalFormat(textureData.format);
    glTextureStorage2D(m_id, 1, internalFormat, m_width, m_height);
    glTextureSubImage2D(
            m_id,
            0,
            0,
            0,
            m_width,
            m_height,
            format,
            GL_UNSIGNED_BYTE,
            textureData.data
    );
    glGenerateTextureMipmap(m_id);
}