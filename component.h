#pragma once

#include "common.h"
#include "game_object.h"

typedef struct Component Component;

Component* CreateComponent(
	const char* name,
	void* data,
	void(*startFunction)(void* data, struct GameObject* gameObject),
	void(*updateFunction)(void* data, struct GameObject* gameObject, float deltaTime)
);

void BindComponent(Component* component, struct GameObject* targetObject);
char* GetComponentName(Component* component);
void* GetComponentData(Component* component);
struct GameObject* GetComponentObject(Component* component);
void StartComponent(Component* component);
void UpdateComponent(Component* component, float deltaTime);
void CleanComponent(Component* component);