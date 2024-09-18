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
