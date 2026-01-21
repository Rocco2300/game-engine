#include "mesh.hpp"

#include <GL/gl3w.h>

#include <iostream>

static glm::vec2 toVec2(aiVector3t<ai_real> aiVec) {
    glm::vec2 ret;
    ret.x = aiVec.x;
    ret.y = aiVec.y;
    return ret;
}

static glm::vec3 toVec3(aiVector3t<ai_real> aiVec) {
    glm::vec3 ret{};
    ret.x = aiVec.x;
    ret.y = aiVec.y;
    ret.z = aiVec.z;
    return ret;
}

Mesh::Mesh(const aiMesh* mesh) {
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        vertex.position = toVec3(mesh->mVertices[i]);
        vertex.normal   = toVec3(mesh->mNormals[i]);

        if (mesh->HasTangentsAndBitangents()) {
            vertex.tangent   = toVec3(mesh->mTangents[i]);
            vertex.bitangent = toVec3(mesh->mBitangents[i]);
        }

        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = toVec2(mesh->mTextureCoords[0][i]);
        }

        m_vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            m_indices.push_back(face.mIndices[j]);
        }
    }

    setupMesh();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    m_vertices = vertices;
    m_indices  = indices;

    setupMesh();
}

void Mesh::setupMesh() {
    glCreateBuffers(1, &m_vbo);
    glNamedBufferStorage(
            m_vbo,
            sizeof(Vertex) * m_vertices.size(),
            &m_vertices[0],
            GL_DYNAMIC_STORAGE_BIT
    );

    glCreateBuffers(1, &m_ebo);
    glNamedBufferStorage(
            m_ebo,
            sizeof(uint32_t) * m_indices.size(),
            &m_indices[0],
            GL_DYNAMIC_STORAGE_BIT
    );

    glCreateVertexArrays(1, &m_vao);

    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(m_vao, m_ebo);

    glEnableVertexArrayAttrib(m_vao, 0);
    glEnableVertexArrayAttrib(m_vao, 1);
    glEnableVertexArrayAttrib(m_vao, 2);
    glEnableVertexArrayAttrib(m_vao, 3);
    glEnableVertexArrayAttrib(m_vao, 4);

    glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    glVertexArrayAttribFormat(m_vao, 2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, tangent));
    glVertexArrayAttribFormat(m_vao, 3, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, bitangent));
    glVertexArrayAttribFormat(m_vao, 4, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));

    glVertexArrayAttribBinding(m_vao, 0, 0);
    glVertexArrayAttribBinding(m_vao, 1, 0);
    glVertexArrayAttribBinding(m_vao, 2, 0);
    glVertexArrayAttribBinding(m_vao, 3, 0);
    glVertexArrayAttribBinding(m_vao, 4, 0);
}