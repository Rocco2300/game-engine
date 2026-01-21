#pragma once

#include "asset_store.hpp"

#include <cstdint>

#include <assimp/mesh.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec3 tangent{};
    glm::vec3 bitangent{};
    glm::vec2 texCoords{};
};

class Mesh {
private:
    friend class SceneRenderer;
    friend class AssetStore<Mesh>;

    Mesh() = default;
    Mesh(const aiMesh* mesh);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void setupMesh();

    uint32_t m_vao{};
    uint32_t m_vbo{};
    uint32_t m_ebo{};

    std::vector<Vertex> m_vertices{};
    std::vector<uint32_t> m_indices{};
};
