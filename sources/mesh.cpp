#include "mesh.hpp"

#include <GL/gl3w.h>

Mesh::Mesh(const aiMesh* mesh) {
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        glm::vec3 temp;
        temp.x = mesh->mVertices[i].x;
        temp.y = mesh->mVertices[i].y;
        temp.z = mesh->mVertices[i].z;
        vertex.position = temp;

        temp.x = mesh->mNormals[i].x;
        temp.y = mesh->mNormals[i].y;
        temp.z = mesh->mNormals[i].z;
        vertex.normal = temp;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 uv;
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = uv;
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
    glNamedBufferStorage(m_vbo, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &m_ebo);
    glNamedBufferStorage(m_ebo, sizeof(uint32_t) * m_indices.size(), &m_indices[0], GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_vao);

    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(m_vao, m_ebo);

    glEnableVertexArrayAttrib(m_vao, 0);
    glEnableVertexArrayAttrib(m_vao, 1);
    glEnableVertexArrayAttrib(m_vao, 2);

    glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));

    glVertexArrayAttribBinding(m_vao, 0, 0);
    glVertexArrayAttribBinding(m_vao, 1, 0);
    glVertexArrayAttribBinding(m_vao, 2, 0);
}