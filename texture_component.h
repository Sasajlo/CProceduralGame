#pragma once

#include "common.h"
#include "component.h"

Component* CreateTextureComponent();
void LoadTexture(Component* textureComponent, const char* path);
void SetActiveTexture(Component* textureComponent, int index);