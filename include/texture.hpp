#pragma once

#include <memory>
#include <cstdint>

class Texture {
private:
    uint32_t m_id;

    int m_width;
    int m_height;
    int m_channelNumber;

    uint8_t* m_data;

public:
    Texture(const std::string& path);

    void bind();
};