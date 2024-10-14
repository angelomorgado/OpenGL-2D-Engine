#version 460 core

in vec3 ourColor;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 customColor = vec3(1.0);

void main()
{
    // vec4 tex = texture(texture1, TexCoords);
    // if (tex.w == 0.0) {
    //     discard;
    // }
    FragColor = texture(texture1, TexCoords) * vec4(ourColor, 1.0) * vec4(customColor, 1.0);
} 
