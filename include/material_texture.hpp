#pragma once

#include "texture.hpp"
#include "asset_store.hpp"

#include <span>
#include <string>
#include <cstdint>
#include <filesystem>

class MaterialTexture : public Texture {
public:
    enum class Type {
        Diffuse,
        Normal,
        Specular,
    };

    MaterialTexture() = default;
    MaterialTexture(const std::filesystem::path& path, Type type);
    MaterialTexture(const TextureData& textureData, Type type);

    void bind() const;

private:
    friend class Program;
    friend class AssetStore<MaterialTexture>;

    Type m_type;

    int getBindUnit() const;
};