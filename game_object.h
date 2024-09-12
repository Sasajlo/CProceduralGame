#pragma once

#include "common.h"
#include "component.h"
#include "window.h"

typedef struct GameObject GameObject;

GameObject* CreateGameObject(const char* name);
void AddComponent(GameObject* gameObject, struct Component* component);
struct Component* GetComponent(GameObject* gameObject, const char* componentName);
char* GetGameObjectName(GameObject* gameObject);

void StartGameObject(GameObject* gameObject);
void UpdateGameObject(GameObject* gameObject, float deltaTime);
void RenderGameObject(GameObject* gameObject, Window* window);