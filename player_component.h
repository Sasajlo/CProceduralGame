#pragma once

#include "common.h"
#include "component.h"

Component* CreatePlayerComponent();
void MovePlayerUp(Component* playerComponent, float amount);