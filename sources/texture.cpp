#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/gl3w.h>

#include <iostream>

Texture::Texture(const std::string& path, Type type) {
    m_type = type;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channelNumber;
    uint8_t* data;
    data = stbi_load(path.c_str(), &width, &height, &channelNumber, 0);

    if (!data) {
        std::cerr << "Failed to load texture " << path << "\nLoading default texture\n";
        width = 1;
        height = 1;
        channelNumber = 3;

        data = new uint8_t[width * height * channelNumber] {255, 0, 255};
    }

    auto format         = getFormat(channelNumber);
    auto internalFormat = getInternalFormat(channelNumber);
    glTextureStorage2D(m_id, 1, internalFormat, width, height);
    glTextureSubImage2D(m_id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(m_id);

    if (!path.empty()) {
        stbi_image_free(data);
    } else {
        delete[] data;
    }
}

void Texture::bind() const {
    glBindTextureUnit(getBindUnit(), m_id);
}

int Texture::getBindUnit() const {
    switch (m_type) {
    case Type::Diffuse:
        return 0;
    case Type::Normal:
        return 1;
    case Type::Specular:
        return 2;
    }

    return 0;
}

int Texture::getFormat(int channelNumber) {
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

int Texture::getInternalFormat(int channelNumber) {
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
