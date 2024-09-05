#pragma once

#include <GL/glew.h>

typedef struct {
	GLuint id;
} Texture;

Texture* loadTexture();