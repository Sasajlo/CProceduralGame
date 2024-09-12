#include "transform_component.h"

typedef struct TransformData
{
    float position[3];
    float rotation[3];
    float scale[3];
} TransformData;

Component* CreateTransformComponent()
{
    TransformData* transformData = malloc(sizeof(TransformData));
    if (transformData == NULL)
    {
        fprintf(stderr, "[Error] Failed to create transform component");
        exit(1);
    }

    transformData->position[0] = 0.0f;
    transformData->position[1] = 0.0f;
    transformData->position[2] = 0.0f;

    transformData->rotation[0] = 0.0f;
    transformData->rotation[1] = 0.0f;
    transformData->rotation[2] = 0.0f;

    transformData->scale[0] = 1.0f;
    transformData->scale[1] = 1.0f;
    transformData->scale[2] = 1.0f;

    return CreateComponent("Transform", transformData, NULL, NULL);
}

float* GetPosition(Component* transformComponent)
{
    TransformData* transformData = (TransformData*)GetComponentData(transformComponent);
    return transformData->position;
}

float* GetRotation(Component* transformComponent)
{
    TransformData* transformData = (TransformData*)GetComponentData(transformComponent);
    return transformData->rotation;
}

float* GetScale(Component* transformComponent)
{
    TransformData* transformData = (TransformData*)GetComponentData(transformComponent);
    return transformData->scale;
}

void SetPosition(Component* transformComponent, float* position)
{
    TransformData* transformData = (TransformData*)GetComponentData(transformComponent);
    transformData->position[0] = position[0];
    transformData->position[1] = position[1];
    transformData->position[2] = position[2];
}

