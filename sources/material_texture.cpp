#include "material_texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/gl3w.h>

#include <iostream>

MaterialTexture::MaterialTexture(const std::filesystem::path& path, Type type) {
    int width, height, channelNumber;
    uint8_t* data;
    data = stbi_load(path.string().c_str(), &width, &height, &channelNumber, 0);

    if (!data) {
        std::cerr << "Failed to load texture " << path << "\nLoading default texture\n";
        width         = 1;
        height        = 1;
        channelNumber = 3;

        data = new uint8_t[width * height * channelNumber]{255, 0, 255};
    }

    m_type   = type;
    m_width  = width;
    m_height = height;

    TextureData textureData{
            .width  = width,
            .height = height,
            .data   = data,
            .format = toTextureFormat(channelNumber)
    };

    setupTexture(textureData);

    if (!path.empty()) {
        stbi_image_free(data);
    } else {
        delete[] data;
    }
}

MaterialTexture::MaterialTexture(const TextureData& textureData, Type type)
    : Texture(textureData) {
    m_type = type;
}

int MaterialTexture::getBindUnit() const {
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

void MaterialTexture::bind() const { Texture::bind(getBindUnit()); }
