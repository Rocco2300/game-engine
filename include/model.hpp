#pragma once

#include <assimp/scene.h>

#include <string>
#include <memory>

#include "mesh.hpp"
#include "material.hpp"

class Model {
private:
    std::string m_path;
    // TODO: bypass lack of default constructor
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    std::vector<std::unique_ptr<Material>> m_materials;

public:
    Model() = default;
    Model(const std::string& path);

private:
    void loadModel(const std::string& path);

    void processNode(const aiNode* node, const aiScene* scene);
    std::unique_ptr<Mesh> processMesh(const aiMesh* mesh, const aiScene* scene);

private:
    friend class Renderer;
};