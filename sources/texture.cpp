#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/gl3w.h>

#include <iostream>

static int getFormat(int channelNumber) {
    switch (channelNumber) {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    }
    return GL_RGB;
}

static int getInternalFormat(int channelNumber) {
    switch (channelNumber) {
    case1:
        return GL_R8;
    case 2:
        return GL_RG8;
    case 3:
        return GL_RGB8;
    case 4:
        return GL_RGBA8;
    }
    return GL_RGB8;
}

Texture::Texture(const std::string& path) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channelNumber, 0);
    if (m_data) {
        auto format = getFormat(m_channelNumber);
        auto internalFormat = getInternalFormat(m_channelNumber);
        glTextureStorage2D(m_id, 1, internalFormat, m_width, m_height);
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateTextureMipmap(m_id);
    } else {
        std::cerr << "Failed to load texture " << path << '\n';
    }

    stbi_image_free(m_data);
}

void Texture::bind() {
    glBindTextureUnit(0, m_id);
}
