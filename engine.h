#pragma once

#include "common.h"

#include "scene.h"

typedef struct Engine Engine;

Engine* CreateEngine(const char* title, int width, int height);
void SetActiveScene(Engine* engine, Scene* scene);
void StartEngine(Engine* engine);
void CleanEngine(Engine* engine);