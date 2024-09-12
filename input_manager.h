#pragma once

#include <GLFW/glfw3.h>

#include "common.h"
#include "window.h"

typedef struct InputManager InputManager;

void InitInputManager();
void UpdateInput(Window* window);
bool IsKeyDown(int keycode);
bool IsKeyPressed(int keycode);
bool IsKeyReleased(int keycode);