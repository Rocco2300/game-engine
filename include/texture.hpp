#pragma once

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

public:
    Texture(Type type, const std::string& path = "");

    void bind();

private:
    int getBindUnit() const;
    int getFormat(int channelNumber);
    int getInternalFormat(int channelNumber);


private:
    friend class Program;
};