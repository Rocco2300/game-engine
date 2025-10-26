#pragma once

#include <assimp/scene.h>

#include <string>
#include <memory>

#include "mesh.hpp"

class Model {
private:
    // TODO: bypass lack of default constructor
    std::vector<std::unique_ptr<Mesh>> m_meshes;

public:
    Model(const std::string& path);

    void draw();

private:
    void loadModel(const std::string& path);

    void processNode(const aiNode* node, const aiScene* scene);
    std::unique_ptr<Mesh> processMesh(const aiMesh* mesh, const aiScene* scene);
};