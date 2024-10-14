# OpenGL 2D Engine
## By [Ângelo Morgado](https://github.com/angelomorgado)

This is a simple 2D engine written in C++ using OpenGL. It is intended to be used to do experiments with 2D graphics. Compatible with Windows and Linux.

### Instalation

On Linux:
    
```bash
sudo apt-get install mesa-common-dev libgl-dev libglfw3-dev libassimp-dev libxrandr-dev libxi-dev libxxf86vm-dev libxcursor-dev libxinerama-dev libxext-dev libxrender-dev libglu1-mesa-dev libfreetype6-dev
```

On Windows:

Follow [this tutorial](https://code.visualstudio.com/docs/cpp/config-mingw).
    
### Scenes

- `CollisionsScene`: A scene that shows objects in the screen moving and colliding with each other.

- `CircleInsideSquareScene`: A scene that shows a square that's movable with the wasd keys and a circle inside the square that can't leave the square.

- `Breakout`: A scene that shows a Breakout game.

### Features

- [x] 2D rendering
- [x] Scene support
- [x] INI file support
- [x] Input handling
- [x] Shader support
- [x] Makefile support for Linux
- [x] Texture support
- [x] AABB Collision detection
- [x] Window Border Collision detection
- [x] Circle Collision detection
- [x] Text rendering
- [x] Audio support
- [ ] VFX support
- [ ] Post-processing support (Framebuffers)
- [ ] Physics support
- [ ] Sprite support
- [ ] Tilemap support

---
## Documentation

[Window](#window)

[Scenes](#scenes)

[Callbacks](#callbacks)

[INI File](#ini-file)

[Shaders](#shaders)

[Textures](#textures)

[Shapes](#shapes)

[Object](#object)

[Collisions](#collisions)

[Text](#text)

---

### Window

The window is where everything is rendered. It is created in the Setup.cpp file. The following code is used to create the window:

```cpp
GLFWwindow* window = Setup::complete_setup(title, screen_width, screen_height, fullscreen, resizable);
```

The window has the dimensions of [-1.0, 1.0] vertically (where 1.0 is the top and vice-versa) and [-1.0, 1.0] horizontally (where 1.0 is the right side and vice-versa). The origin is at the center of the window.

```cpp
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
standardShader.load("standard"); // You can also load a shader from a filename and it will load the vertex, fragment and geometry shaders with the same name. They must be in the Shaders folder and also have the ".vert", ".frag" and ".geom" extensions

// In the render method of the scene
standardShader.use();

// In the clean method of the scene
standardShader.clean();
```

If you have uniforms in the shader, you can set them like this:

```cpp
unsinged int getID();
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

---

### Textures

This engine can apply textures to objects. To load a texture:
    
```cpp
Texture texture;

// In the load method of the scene
texture.load("Textures/texture.png");

// In the render method of the scene before drawing the object
texture.bind(int textureUnit = 0); // The texture unit is optional and is used to bind the texture to a specific texture unit
```

You may also unbind and clean the texture after rendering the object:

```cpp
texture.unbind();

// In the clean method of the scene
texture.clean();
```

To get the texture ID:

```cpp
GLuint textureID = texture.getID();
```

---

### Shapes

The engine has a class that can create predefined shapes. Its vertex attributes are entirely customizable with the `vertexAttributes` attribute. Currently there are four shapes available: square, triangle, circle, and screen.

To create a shape:

```cpp
Shape shape;
shape.createSquare();
shape.createTriangle();
shape.createCircle(numberOfSegments); // The number of segments is so you can create a circle with more or less vertices (More segments = more perfect circle however more computational power is needed)
shape.createScreen(); // Creates a screen that covers the entire window
```

In order to send the shape to the GPU, it uses the `square.vertices.data()`, `square.vertices.size()`, `square.indices.data()`, and `square.indices.size()` methods. Here is an example of how to send the square to the GPU:

```cpp
glGenVertexArrays(1, &VAO);  // Generate VAO
glBindVertexArray(VAO);      // Bind VAO
// Generate and bind Vertex Buffer Object (VBO)
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
// Copy our vertices array into the buffer for OpenGL to use
glBufferData(GL_ARRAY_BUFFER, square.vertices.size() * sizeof(float), square.vertices.data(), GL_STATIC_DRAW);
// Generate and bind Element Buffer Object (EBO)
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
// Copy our vertices array into the buffer for OpenGL to use
glBufferData(GL_ELEMENT_ARRAY_BUFFER, square.indices.size() * sizeof(unsigned int), square.indices.data(), GL_STATIC_DRAW); 
// Set the vertex attributes pointers
for (const auto& attr : shape.vertexAttributes) {
    glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.pointer);
    glEnableVertexAttribArray(attr.index);  // Enable the attribute
}
// Unbind VAO and VBO for safety
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
```

Shapes have attributes that can be accessed to retrieve information about the shape:

```cpp
numberOfVertices = shape.numberOfVertices;
vertices = shape.vertices;
indices = shape.indices;
size = shape.size;
radius = shape.radius; // Only for the circle shape
std::vector<VertexAttribute> vertexAttributes;
GLenum drawFormat; // E.g., GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_LINE_LOOP, etc.
```
---

### Object

The Object class represents a renderable object that can be loaded with a shape, shader, and textures, and transformed through translation, rotation, and scaling. Below is how to use it:

```cpp

Object object;

// In the load method of the scene
object.load(shape, position, rotation, scale);

// In the render method of the scene
object.render(shader, texture);

// In the clean method of the scene
object.clean();
```

This class has more methods that aim to facilitate its use:

```cpp
void load(Shape shape, Shader shader, std::vector<Texture> textures = {}, glm::vec2 position = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 scale = glm::vec2(0.0f)) // Loads the object to the GPU

void render() // Renders the object

void clean() // Cleans the object from the GPU

void move(glm::vec3 direction) // Moves the object in a direction (instead of setting the position)

// Getters
glm::vec2 getPosition()
float getRotation()
glm::vec2 getScale()
glm::vec2 getSize() // Returns the size of the object (Scale * Shape.size)
glm::mat4 getTransform()

// Setters
void setPosition(glm::vec2 position)
void setRotation(float rotation)
void setScale(glm::vec2 scale)
void setTransform(glm::mat4 transform) // Sets the transformation matrix if you want to set it outside the class
void setColor(glm::vec3 color)
```

---

### Collisions

This engine has a namespace that can detect collisions between objects. The following methods are available:

```cpp
bool checkAABBCollision(Object& obj1, Object& obj2) // Does AABB collision detection and returns true if obj1 is colliding with obj2

bool checkCircleCollision(Object& circle, Object& obj) // Does Circle collision detection and returns true if circle is colliding with obj

unsigned int  checkWindowCollision(Object& obj) // Checks if the object is colliding with the window and returns the border that is colliding with the object (0 = No collision, 2 = top, 3 = right, 4 = bottom, 5 = left, 6+:Corner)

```

---

### Text

This engine has a class that can render text in the screen. The text is rendered using the [FreeType](https://www.freetype.org/) library. To use it:

```cpp
Font text;

// In the load method of the scene
text.loadFont("Media/Fonts/fontname", int fontSize, Shader &textShader, int screenWidth, int screenHeight);

// In the render method of the scene
text.renderText("Text to render", glm::vec2 position, float scale, glm::vec3 color);

// In the clean method of the scene
text.clean();
```

---

### Audio

This engine uses the [miniaudio](https://miniaud.io/) library. In order to play it please follow the instructions in its documentation.
