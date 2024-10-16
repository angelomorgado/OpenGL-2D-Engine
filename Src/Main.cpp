#include <iostream>
#include <memory>
#include <INIReader.h>
#include <SceneManager.hpp>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <Scenes/CollisionsScene.hpp>
#include <Scenes/CircleInsideSquareScene.hpp>
#include <Scenes/Breakout.hpp>

int main() {
    SceneManager& sceneManager = SceneManager::getInstance();

    // Register scenes
    sceneManager.registerScene("CollisionsScene", []() { return std::make_shared<CollisionsScene>(); });
    sceneManager.registerScene("CircleInsideSquareScene", []() { return std::make_shared<CircleInsideSquareScene>(); });
    sceneManager.registerScene("Breakout", []() { return std::make_shared<Breakout>(); });

    // Load a scene by name
    INIReader reader("Config.ini");
    std::string sceneName = reader.Get("Scene", "active_scene", "StandardScene");
    // std::string sceneName = "StandardScene"; // Alternatively, you can hardcode the scene name
    std::cout << "Loading scene: " << sceneName << std::endl;
    auto scene = sceneManager.loadScene(sceneName);

    if (scene) {
        scene->load();
        while(!glfwWindowShouldClose(scene->getWindow())) {
            scene->update();
            scene->render();
        }
        scene->clean();
    } else {
        std::cout << "Scene not found!\n";
    }

    return 0;
}