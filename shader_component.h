#pragma once

#include <GL/glew.h>

#include "common.h"
#include "component.h"

Component* CreateShaderComponent(char* vertexShaderPath, char* fragmentShaderPath);
GLuint GetAttributeLocation(Component* shaderComponent, const char* attributeName);
GLuint GetUniformLocation(Component* shaderComponent, const char* uniformName);
void UseShaderProgram(Component* shaderComponent);

void CleanShader(Component* shader);