#include "renderer_component.h"
#include "mesh_component.h"
#include "shader_component.h"
#include "transform_component.h"
#include "texture_component.h"
#include "scene.h"
#include "math2.h"

typedef struct RendererData
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    void(*render)(Component* rendererComponent);
} Data;

Component* CreateRendererComponent(void(*render)(Component* rendererComponent))
{
    Data* data = malloc(sizeof(Data));
    if (data == NULL)
    {
        fprintf(stderr, "[Error] Failed to create renderer component");
        exit(1);
    }

    glGenVertexArrays(1, &data->vao);
    glGenBuffers(1, &data->vbo); 
    glGenBuffers(1, &data->ebo);
    data->render = render;

    Component* component = CreateComponent("Renderer", data, NULL, NULL);
    return component;
}

void RenderMesh(Component* rendererComponent)
{
    GameObject* gameObject = GetComponentObject(rendererComponent);
    Data* rendererData = (Data*)GetComponentData(rendererComponent);

    // Get mesh component
    Component* meshComponent = GetComponent(gameObject, "Mesh");
    if (meshComponent == NULL)
    {
        fprintf(stderr, "[Error] Missing mesh component on object: %s\n", GetGameObjectName(gameObject));
        exit(1);
    }

    // Get shader component
    Component* shaderComponent = GetComponent(gameObject, "Shader");
    if (shaderComponent == NULL)
    {
        fprintf(stderr, "[Error] Missing shader component on object: %s\n", GetGameObjectName(gameObject));
        exit(1);
    }

    // Get transform component
    Component* transformComponent = GetComponent(gameObject, "Transform");
    if (transformComponent == NULL)
    {
        fprintf(stderr, "[Error] Missing transform component on object: %s\n", GetGameObjectName(gameObject));
        exit(1);
    }

    // Get texture component
    Component* textureComponent = GetComponent(gameObject, "Texture");

    // Bind shader program
    UseShaderProgram(shaderComponent);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Bind a VAO
    glBindVertexArray(rendererData->vao);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, rendererData->vbo);
    glBufferData(GL_ARRAY_BUFFER, GetVertexCount(meshComponent) * 11 * sizeof(GLfloat), GetVertices(meshComponent), GL_STATIC_DRAW);

    // Bind position atribute
    GLint positionAttributeLoc = GetAttributeLocation(shaderComponent, "position");
    glVertexAttribPointer(positionAttributeLoc, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(positionAttributeLoc);

    // Bind color atribute
    GLint colorAttributeLoc = GetAttributeLocation(shaderComponent, "color");
    glVertexAttribPointer(colorAttributeLoc, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    glEnableVertexAttribArray(colorAttributeLoc);

    GLint textureAttributeLoc = GetAttributeLocation(shaderComponent, "texCoord");
    glVertexAttribPointer(textureAttributeLoc, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttributeLoc);

    // Create an EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetIndexCount(meshComponent) * sizeof(GLuint), GetIndices(meshComponent), GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);  // Activate the texture unit
    if (textureComponent != NULL)
        SetActiveTexture(textureComponent, 0);

    GLint useTextureLoc = GetUniformLocation(shaderComponent, "useTexture");
    glUniform1i(useTextureLoc, textureComponent != NULL);

    // Calculate model matrix
    GLfloat model[16];
    CreateModelMatrix(GetPosition(transformComponent), GetRotation(transformComponent), GetScale(transformComponent), model);

    GLint modelLoc = GetUniformLocation(shaderComponent, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

    // Calculate 2D view matrix
    GLfloat view[16];
    Camera* camera = GetMainCamera();
    float* cameraPosition = GetCameraPosition(camera);
    Create2DViewMatrix(cameraPosition[0], cameraPosition[1], view);

    GLint viewLoc = GetUniformLocation(shaderComponent, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);

    // Calculate 2D projection matrix
    GLfloat projection[16];
    Create2DProjectionMatrix(1280.0f / 720.0f , projection);

    GLint projectionLoc = GetUniformLocation(shaderComponent, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);

    // Draw mesh
    glDrawElements(GL_TRIANGLES, GetIndexCount(meshComponent), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

Component* CreateMeshRendererComponent()
{
    return CreateRendererComponent(RenderMesh);
}

void RendererRender(Component* rendererComponent)
{
    GameObject* gameObject = GetComponentObject(rendererComponent);
    Data* rendererData = (Data*)GetComponentData(rendererComponent);
    if (rendererData == NULL)
    {
        fprintf(stderr, "[Error] Failed to render game object: %s", GetGameObjectName(gameObject));
        exit(1);
    }

    rendererData->render(rendererComponent);
}
