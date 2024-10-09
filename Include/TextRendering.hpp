#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <string>
#include <glm/glm.hpp>
#include <Shader.hpp>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

class Font {
    public:
        // Initialize the text rendering module and load a font
        bool loadFont(const std::string& fontPath, int fontSize, Shader &shader, int screenWidth, int screenHeight);

        // Render text on the screen
        void renderText(const std::string& text, glm::vec2 position, float scale, glm::vec3 color);

        // Clean up resources
        void clean();

    private:
        struct Character {
            unsigned int TextureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        FT_Library ft;
        FT_Face face;
        unsigned int VAO, VBO;
        std::map<GLchar, Character> characters;
        Shader textShader;
};

#endif