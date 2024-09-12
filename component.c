#include "component.h"

struct Component 
{
	char name[MAX_COMPONENT_NAME_LEN];
	GameObject* gameObject;
	void* data;
	void(*startFunction)(void* data, GameObject* gameObject);
	void(*updateFunction)(void* data, GameObject* gameObject, float deltaTime);
};

Component* CreateComponent(
	const char* name,
	void* data, 
	void(*startFunction)(void* data, GameObject* gameObject),
	void(*updateFunction)(void* data, GameObject* gameObject, float deltaTime))
{
	// Allocate memmory for engine
	Component* component = malloc(sizeof(Component));
	if (component == NULL)
	{
		fprintf(stderr, "[Error] Failed to create component");
		exit(1);
	}

	strcpy_s(component->name, MAX_COMPONENT_NAME_LEN, name);
	component->gameObject = NULL;
	component->data = data;
	component->startFunction = startFunction;
	component->updateFunction = updateFunction;

	return component;
}

void BindComponent(Component* component, GameObject* targetObject)
{
	component->gameObject = targetObject;
}

char* GetComponentName(Component* component)
{
	char name[MAX_COMPONENT_NAME_LEN];
	strcpy_s(name, MAX_COMPONENT_NAME_LEN, component->name);
	return name;
}

void* GetComponentData(Component* component)
{
	return component->data;
}

GameObject* GetComponentObject(Component* component)
{
	return component->gameObject;
}

void StartComponent(Component* component)
{
	if (component->startFunction != NULL)
		component->startFunction(component->data, component->gameObject);
}

void UpdateComponent(Component* component, float deltaTime)
{
	if (component->updateFunction != NULL)
		component->updateFunction(component->data, component->gameObject, deltaTime);
}

void CleanComponent(Component* component)
{
	if (component == NULL)
		return; // Nothing to clean

	// Clean component
	free(component);
}
