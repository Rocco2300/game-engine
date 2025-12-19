#pragma once

#include <queue>
#include <string>
#include <memory>
#include <filesystem>
#include <unordered_map>

template <typename T>
class AssetStore {
public:
    AssetStore() {
        m_availableIds = std::queue<int>();
        for (int i = 0; i <= 256; i++) {
            m_availableIds.push(i);
        }
    }

    AssetStore(const std::filesystem::path& path) {
        m_availableIds = std::queue<int>();
        for (int i = 0; i <= 256; i++) {
            m_availableIds.push(i);
        }

        m_path = path;
    }

    void setPath(const std::filesystem::path& path) {
        m_path = path;
    }

    T* get(int id) {
        if (m_assets.find(id) == m_assets.end()) {
            return nullptr;
        }

        return &m_assets.at(id);
    }

    T* get(const std::string& name) {
        if (!m_nameToId.count(name)) {
            return nullptr;
        }

        auto id = m_nameToId[name];
        return &m_assets.at(id);
    }

    template <typename ...Args>
    int load(const std::string& name, Args... args) {
        if (m_nameToId.count(name)) {
            return m_nameToId.at(name);
        }

        auto id = m_availableIds.front();
        m_availableIds.pop();

        auto fullPath = m_path / name;
        auto object = T(fullPath.string(), args...);

        m_nameToId[name] = id;
        m_assets.emplace(id, object);

        return id;
    }

    template <typename ...Args>
    int emplace(const std::string& name, Args... args) {
        auto id = m_availableIds.front();
        m_availableIds.pop();

        auto object = T(args...);

        m_nameToId[name] = id;
        m_assets.emplace(id, object);

        return id;
    }

private:
    std::filesystem::path m_path;

    std::unordered_map<int, T> m_assets;
    std::unordered_map<std::string, int> m_nameToId;

    std::queue<int> m_availableIds;
};