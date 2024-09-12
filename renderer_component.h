#pragma once

#include <GL/glew.h>

#include "common.h"
#include "game_object.h"

Component* CreateMeshRendererComponent();
void RendererRender(Component* renderer);