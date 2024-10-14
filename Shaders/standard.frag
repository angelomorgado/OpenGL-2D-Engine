#version 460 core

in vec3 ourColor;
out vec4 FragColor;

uniform vec3 customColor;

void main()
{
    FragColor = vec4(ourColor, 1.0) * vec4(customColor, 1.0);
}