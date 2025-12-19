#include "serializer.hpp"

#include "scene.hpp"
#include "asset_manager.hpp"

#include <fstream>
#include <iostream>

json Serializer::m_json{};
std::filesystem::path Serializer::m_path{};
bool Serializer::m_loading{};
const Scene* Serializer::m_currentScene{};
std::vector<std::vector<std::string>> Serializer::m_assetPaths{};

void Serializer::setPath(const std::filesystem::path& path) { m_path = path; }

void Serializer::loadSceneFile(const std::string& name) {
    auto path = m_path / name;
    std::ifstream in(path);

    m_json = json::parse(in);

    in.close();

    m_loading = true;
}

void Serializer::serializeScene(const Scene& scene) {
    if (m_loading) {
        return;
    }

    m_currentScene = &scene;

    m_json = json({{"assets", m_assetPaths}});
    if (m_currentScene) {
        auto& sceneRef = *m_currentScene;
        m_json.push_back({"scene", sceneRef});
    }

    writeToFile();
}

void Serializer::serializeAssetName(const std::string& type, const std::string& name) {
    if (m_loading) {
        return;
    }

    m_assetPaths.push_back({type, name});

    m_json = json({{"assets", m_assetPaths}});
    if (m_currentScene) {
        auto& scene = *m_currentScene;
        m_json.push_back({"scene", scene});
    }
}

void Serializer::serializeAssetName(
        const std::string& type,
        const std::string& name,
        const std::string& textureType
) {
    if (m_loading) {
        return;
    }

    m_assetPaths.push_back({type, name, textureType});

    m_json = json({{"assets", m_assetPaths}});
    if (m_currentScene) {
        auto& scene = *m_currentScene;
        m_json.push_back({"scene", scene});
    }
}

void Serializer::writeToFile() {
    auto path = m_path / "scene.json";
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error opening output file!\n";
    }

    out << std::setw(4) << m_json;
    out.close();
}

void Serializer::deserializeAssets() {
    auto j = m_json.at("assets");
    j.get_to(m_assetPaths);

    for (const auto& assetPair : j) {
        auto type = assetPair[0].get<std::string>();
        auto name = assetPair[1].get<std::string>();

        if (type == "model") {
            AssetManager::loadModel(name);
            std::cout << "Loading serialized model " << name << '\n';
        } else if (type == "texture") {
            auto textureTypeStr = assetPair[2].get<std::string>();
            Texture::Type textureType;
            if (textureTypeStr == "normal") {
                textureType = Texture::Type::Normal;
            } else if (textureTypeStr == "specular") {
                textureType = Texture::Type::Specular;
            } else {
                textureType = Texture::Type::Diffuse;
            }

            std::cout << "Loading serialized " << textureTypeStr << " texture " << name << "\n";
            AssetManager::loadTexture(name, textureType);
        }
    }
}

void Serializer::deserializeScene(Scene& scene) {
    m_json.at("scene").get_to(scene);
    m_currentScene = &scene;
}