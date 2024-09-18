#version 460 core

in vec3 ourColor;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoords) * vec4(ourColor, 1.0f);
} 