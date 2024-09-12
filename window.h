#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common.h"

typedef struct Window Window;

Window* CreateWindow(const char* title, int width, int height);
bool ShouldWindowClose(Window* window);
void ClearWindow(Window* window);
void UpdateWindow(Window* window);
void CleanWindow(Window* window);

void SetMouseCursor(Window* window, GLFWcursor* cursor);
void SetMouseCallbacks(Window* window, GLFWcursorposfun mousePositionCallback, GLFWmousebuttonfun mouseButtonCallback);
bool GetKey(Window* window, int keycode);