#include "player_component.h"
#include "transform_component.h"
#include "input_manager.h"
#include "util.h"

#define SPEED 1.0f

typedef struct RendererData
{
    int x;
} Data;

void Start(void* data, GameObject* gameObject)
{
  
}

void Update(void* data, GameObject* gameObject, float deltaTime)
{
    Component* transform = GetComponent(gameObject, "Transform");
    float* position = GetPosition(transform);

    if (IsKeyDown(GLFW_KEY_D))
    {
        position[0] += SPEED * deltaTime;
    }

    if (IsKeyDown(GLFW_KEY_A))
    {
        position[0] -= SPEED * deltaTime;
    }

    if (IsKeyDown(GLFW_KEY_W))
    {
        position[1] += SPEED * deltaTime;
    }

    if (IsKeyDown(GLFW_KEY_S))
    {
        position[1] -= SPEED * deltaTime;
    }
}

Component* CreatePlayerComponent()
{
    Data* data = malloc(sizeof(Data));
    if (data == NULL)
    {
        fprintf(stderr, "[Error] Failed to create data in player component");
        exit(2);
    }

    return CreateComponent("Player", data, Start, Update);
}