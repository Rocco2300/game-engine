#pragma once

#include <queue>
#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class AssetStore {
private:
    std::string m_path;

    std::unordered_map<std::string, int> m_nameToId;
    std::unordered_map<int, std::unique_ptr<T>> m_assets;

    std::queue<int> m_availableIds;

public:
    AssetStore() {
        for (int i = 0; i <= 256; i++) {
            m_availableIds.push(i);
        }
    }

    AssetStore(const std::string& path) {
        for (int i = 0; i <= 256; i++) {
            m_availableIds.push(i);
        }

        m_path = path;
    }

    void setPath(const std::string& path) {
        m_path = path;
    }

    T& get(int id) {
        return *m_assets[id];
    }

    T& get(const std::string& name) {
        auto id = m_nameToId[name];
        return *m_assets[id];
    }

    template <typename ...Args>
    int load(const std::string& name, Args... args) {
        auto id = m_availableIds.front();
        m_availableIds.pop();

        auto asset = std::make_unique<T>(args...);

        m_nameToId[name] = id;
        m_assets[id] = std::move(asset);

        return id;
    }
};