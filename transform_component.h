#pragma once

#include "common.h"
#include "component.h"

Component* CreateTransformComponent();
float* GetPosition(Component* transformComponent);
float* GetRotation(Component* transformComponent);
float* GetScale(Component* transformComponent);

void SetPosition(Component* transformComponent, float* position);
void SetRotation(Component* transformComponent, float* rotation);
void SetScale(Component* transformComponent, float* scale);