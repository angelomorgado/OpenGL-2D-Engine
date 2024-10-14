#version 460 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 customColor = vec3(1.0);

void main()
{
    FragColor = texture(texture1, TexCoords) * vec4(customColor, 1.0);
} 