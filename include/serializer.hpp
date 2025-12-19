#pragma once

#include "json.hpp"

class Scene;

class Serializer {
public:
    static void setPath(const std::filesystem::path& path);

    static void loadSceneFile(const std::string& name);

    static void serializeScene(const Scene& scene);
    static void serializeAssetName(const std::string& type, const std::string& name);
    static void serializeAssetName(
            const std::string& type,
            const std::string& name,
            const std::string& textureType
    );

    static void deserializeAssets();
    static void deserializeScene(Scene& scene);

private:
    Serializer() = default;

    static void writeToFile();

    static json m_json;
    static bool m_loading;
    static std::filesystem::path m_path;

    static const Scene* m_currentScene;
    static std::vector<std::vector<std::string>> m_assetPaths;
};