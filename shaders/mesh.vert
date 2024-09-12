#version 450 core

in vec3 position;
in vec3 color;
in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int useTexture;

out vec3 Color;
out vec2 TexCoord;
out float UseTexture;

void main()
{
    Color = color;
    TexCoord = texCoord;
    UseTexture = float(useTexture);

    gl_Position = projection * view * model * vec4(position, 1.0);
}
