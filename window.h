#pragma once

#include "common.h"

typedef struct Window Window;

Window* CreateWindow(const char* title, int width, int height);
bool ShouldWindowClose(Window* window);
void ClearWindow(Window* window);
void UpdateWindow(Window* window);
void CleanWindow(Window* window);

bool GetKey(Window* window, int keycode);