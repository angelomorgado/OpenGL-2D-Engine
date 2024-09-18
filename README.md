# OpenGL 2D Engine
## By [Ângelo Morgado](https://github.com/angelomorgado)

This is a simple 2D engine written in C++ using OpenGL. It is intended to be used to do experiments with 2D graphics. Compatible with Windows and Linux.

### Instalation

On Linux:
    
```bash
sudo apt-get install mesa-common-dev libgl-dev libglfw3-dev libassimp-dev libxrandr-dev libxi-dev libxxf86vm-dev libxcursor-dev libxinerama-dev libxext-dev libxrender-dev libglu1-mesa-dev
```

On Windows:

Follow [this tutorial](https://code.visualstudio.com/docs/cpp/config-mingw).
    
### Scenes

- StandardScene: A scene that renders a simple window.

### Features

- [x] 2D rendering
- [x] Scene support
- [x] INI file support
- [x] Input handling
- [x] Shader support
- [x] Makefile support for Linux
- [ ] 2D Object import/file from file/image
- [ ] Sprite support
- [ ] Collision detection
- [ ] Text rendering
- [ ] Audio support
- [ ] Physics support
- [ ] Tilemap support

---
## Documentation

[Scenes](#scenes)

[Callbacks](#callbacks)

[INI File](#ini-file)

[Shaders](#shaders)

---

### Scenes

Scenes are a vital part of this template. They are used to separate different parts of the game, such as the main menu, the game itself, and the credits. Each scene must inherit from the Scene class and implement the following methods:

```cpp
class StandardScene : public Scene {
public:
    StandardScene();
    void load() override;
    void update() override;
    void render() override;
    int clean() override;
    GLFWwindow* getWindow() override;
};
```

You also have to create a namespace to register it in the SceneManager:

```cpp
// Register this scene to the scene manager
namespace {
    bool isRegistered = []() {
        SceneManager::getInstance().registerScene("StandardScene", []() -> std::shared_ptr<Scene> {
            return std::make_shared<StandardScene>();
        });
        return true;
    }();
}
```

After that you have to add this line to the Main.cpp file:

```cpp
sceneManager.registerScene("StandardScene", []() { return std::make_shared<StandardScene>(); });
```

To load a scene, you have to call the following method, similar to how it is done in the Main.cpp file:

```cpp
auto scene = sceneManager.loadScene(sceneName);
```
---

### Callbacks

This engine uses callbacks to handle input and update the scene. If the scene has its own callback function it can be defined in the scene class. However, if the scene uses the same callback as other scenes, the callback function must be defined in the Callbacks class in order to avoid code duplication and keep it organized.

To define mouse callbacks:
```cpp
// In the constructor of the scene
// Lock Mouse
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // In order to lock the mouse in the window (Optional)
glfwSetCursorPosCallback(window, Callbacks::mouse_callback_function);
```

To call the keyboard callback:
```cpp
// In the main loop
Callbacks::keyboard_callback_function(window); // If the callback is defined in the Callbacks class

// or 

keyboard_callback_function(); // If the callback is defined in the scene class
```
---

### INI File

The engine uses the [inih](https://github.com/benhoyt/inih) library to read INI files. The INI file must have the following structure:

```ini
[Window]
title=StandardScene
width=800
height=600
fullscreen=false
resizable=true

[Scene]
active_scene=StandardScene
```

In order to read the INI file, the following code must be used:

```cpp
#include <INIReader.h>

INIReader reader("Config.ini");
std::string title = reader.Get("Window", "title", "Window");
int screen_width  = reader.GetInteger("Window", "width", 800);
bool fullscreen   = reader.GetBoolean("Window", "fullscreen", false);
```

---

### Shaders

The engine uses shaders to render the scene. The shaders must be defined in the Shader class. To create a new shader:

```cpp
Shader standardShader;

// In the load method of the scene
standardShader.load("Shaders/standard.vert", "Shaders/standard.frag"); // You can also load a geometry shader but it is optional

// In the render method of the scene
standardShader.use();
```

If you have uniforms in the shader, you can set them like this:

```cpp
void setBool(std::string& name, bool value);
void setInt(std::string& name, int value);
void setFloat(std::string& name, float value);
void setVec2(std::string& name,  glm::vec2& value);
void setVec2(std::string& name, float x, float y);
void setVec3(std::string& name,  glm::vec3& value);
void setVec3(std::string& name, float x, float y, float z);
void setVec4(std::string& name,  glm::vec4& value);
void setVec4(std::string& name, float x, float y, float z, float w);
void setMat2(std::string& name,  glm::mat2& mat);
void setMat3(std::string& name,  glm::mat3& mat);
void setMat4(std::string& name,  glm::mat4& mat);
```