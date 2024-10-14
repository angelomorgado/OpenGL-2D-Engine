#version 460 core

in vec3 ourColor;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoords) * vec4(ourColor, 1.0);
} 