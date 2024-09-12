#include "texture_component.h"

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct TextureData
{
    GLuint *textures;
    int count;
    GLuint activeTexture;
} TextureData;

Component* CreateTextureComponent()
{
    TextureData* textureData = malloc(sizeof(TextureData));
    if (textureData == NULL)
    {
        fprintf(stderr, "[Error] Failed to create texture component");
        exit(1);
    }

    textureData->textures = (GLuint*)malloc(MAX_TEXTURES * sizeof(GLuint));
    textureData->count = 0;
    textureData->activeTexture = 0;

    return CreateComponent("Texture", textureData, NULL, NULL);
}

void LoadTexture(Component* textureComponent, const char* path)
{
    TextureData* textureData = (TextureData*)GetComponentData(textureComponent);

    if (textureData->count == MAX_TEXTURES)
        return;

    // Load the image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {

        glGenTextures(1, &textureData->textures[textureData->count]);
        glBindTexture(GL_TEXTURE_2D, textureData->textures[textureData->count]);
        ++(textureData->count);

        // Set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load the texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        // Generate mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        // Handle error
        printf("Failed to load texture\n");
        exit(1);
    }
}

void SetActiveTexture(Component* textureComponent, int index)
{
    TextureData* textureData = (TextureData*)GetComponentData(textureComponent);

    if (textureData->count == 0)
        return;

    textureData->activeTexture = textureData->textures[index];
    glBindTexture(GL_TEXTURE_2D, textureData->activeTexture);
}
