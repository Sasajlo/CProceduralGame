
#include "shader_component.h"
#include "util.h"

typedef struct ShaderData {
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
} ShaderData;

Component* CreateShaderComponent(char* vertexShaderPath, char* fragmentShaderPath)
{
    ShaderData* shaderData = malloc(sizeof(ShaderData));
    if (shaderData == NULL)
    {
        fprintf(stderr, "[Error] Failed to create shader component");
        exit(1);
    }

    // Create and compile the vertex shader
    shaderData->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = ReadFileToString(vertexShaderPath);
    glShaderSource(shaderData->vertexShader, 1, &vertexSource, NULL);
    glCompileShader(shaderData->vertexShader);

    // Check for compile errors
    GLint status;
    glGetShaderiv(shaderData->vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shaderData->vertexShader, 512, NULL, buffer);
        fprintf(stderr, "Vertex Shader Compile Error: %s\n", buffer);
    }

    // Create and compile the fragment shader
    shaderData->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = ReadFileToString(fragmentShaderPath);
    glShaderSource(shaderData->fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(shaderData->fragmentShader);

    // Check for compile errors
    glGetShaderiv(shaderData->fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shaderData->fragmentShader, 512, NULL, buffer);
        fprintf(stderr, "Fragment Shader Compile Error: %s\n", buffer);
    }

    // Link the vertex and fragment shader into a shader program
    shaderData->program = glCreateProgram();
    glAttachShader(shaderData->program, shaderData->vertexShader);
    glAttachShader(shaderData->program, shaderData->fragmentShader);
    glLinkProgram(shaderData->program);

    return CreateComponent("Shader", shaderData, NULL, NULL);
}

GLuint GetAttributeLocation(Component* shaderComponent, const char* attributeName)
{
    ShaderData* shaderData = (ShaderData*)GetComponentData(shaderComponent);
    return glGetAttribLocation(shaderData->program, attributeName);
}

GLuint GetUniformLocation(Component* shaderComponent, const char* uniformName)
{
    ShaderData* shaderData = (ShaderData*)GetComponentData(shaderComponent);
    return glGetUniformLocation(shaderData->program, uniformName);
}

void UseShaderProgram(Component* shaderComponent)
{
    ShaderData* shaderData = (ShaderData*)GetComponentData(shaderComponent);
    glUseProgram(shaderData->program);
}

void cleanShaderComponent(Component* shader)
{
    /*glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);
    glDeleteProgram(shader->program);*/
    free(shader);
}
