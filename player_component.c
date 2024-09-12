#include "player_component.h"

#include <math.h>

#include "transform_component.h"
#include "input_manager.h"
#include "util.h"
#include "math2.h"

#define SPEED 1.0f

typedef struct RendererData
{
    int x;
} Data;

void Start(void* data, GameObject* gameObject)
{
    Component* transform = GetComponent(gameObject, "Transform");
    float* scale = GetScale(transform);
    scale[0] = 0.2f;
    scale[1] = 0.2f;
}

// Calculate the angle from the player's position to the mouse cursor and apply it to the rotation
void RotateToCursor(Component* transform)
{
    // Get the mouse position in screen space
    float* mousePosition = GetMousePosition();

    // Get the player's position in world space
    float* position = GetPosition(transform);

    // Convert mouse position to normalized device coordinates (NDC)
    float scaledMousePositionX = mousePosition[0] / 1280.0f * 2.0f - 1.0f;
    float scaledMousePositionY = mousePosition[1] / 720.0f * 2.0f - 1.0f;

    // Calculate the angle (in radians) using atan2 (handles the full 360 degrees)
    float angle = atan2f(scaledMousePositionX, scaledMousePositionY);

    // Convert the angle to degrees (optional, depending on how you handle rotations)
    float angleInDegrees = angle * (180.0f / PI);

    // Apply the rotation to the player's transform
    float* rotation = GetRotation(transform);
    rotation[2] = angleInDegrees - 90.0f;
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

    RotateToCursor(transform);
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