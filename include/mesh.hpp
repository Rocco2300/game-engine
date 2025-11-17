#pragma once

#include <cstdint>

#include <assimp/mesh.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 texCoords{};
};

class Mesh {
private:
    uint32_t m_vao{};
    uint32_t m_vbo{};
    uint32_t m_ebo{};

    std::vector<Vertex> m_vertices{};
    std::vector<uint32_t> m_indices{};

public:
    Mesh() = default;
    Mesh(const aiMesh* mesh);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void draw();
private:
    void setupMesh();

private:
    friend class Renderer;
};
