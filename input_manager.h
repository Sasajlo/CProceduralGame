#pragma once

#include "common.h"
#include "window.h"

typedef struct InputManager InputManager;

void InitInputManager(Window* window);
void UpdateInput(Window* window);
bool IsKeyDown(int keycode);
bool IsKeyPressed(int keycode);
bool IsKeyReleased(int keycode);
float* GetMousePosition();