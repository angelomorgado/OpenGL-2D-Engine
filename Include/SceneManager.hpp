#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "Scene.hpp"

class SceneManager {
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    void registerScene(const std::string& name, std::function<std::shared_ptr<Scene>()> creator) {
        sceneMap[name] = creator;
    }

    std::shared_ptr<Scene> loadScene(const std::string& name) {
        if (sceneMap.find(name) != sceneMap.end()) {
            return sceneMap[name]();
        } else {
            return nullptr;
        }
    }

private:
    SceneManager() {}
    
    // Add this line to declare the sceneMap
    std::unordered_map<std::string, std::function<std::shared_ptr<Scene>()>> sceneMap;
};

#endif // SCENEMANAGER_HPP
