#version 450 core

in vec3 Color;       // The color passed to the shader
in vec2 TexCoord;    // The texture coordinates
in float UseTexture; // Flag to determine if texture should be used

out vec4 FragColor;  // The final output color

uniform sampler2D mainTexture; // The texture to sample

void main()
{
    vec4 textureColor;

    // Check if texture should be used
    if (UseTexture == 1.0) {
        // Sample the texture at the given texture coordinates
        textureColor = texture(mainTexture, TexCoord);
        // Combine the texture color and the passed color
        FragColor = vec4(textureColor.rgb * Color, textureColor.a);
    } else {
        // If texture is not used, use just the passed color
        FragColor = vec4(Color, 1.0);
    }
}
