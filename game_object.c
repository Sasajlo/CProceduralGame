#include "game_object.h"
#include "renderer_component.h"

typedef struct ComponentListElement {
	Component* component;
	struct ComponentListElement* next;
} ComponentListElement;

struct GameObject {
	ulong id;
	char name[MAX_OBJECT_NAME_LEN];
	ComponentListElement* components;
	int componentCount;
};

static ulong idCounter;

GameObject* CreateGameObject(const char* name)
{
	GameObject* gameObject = malloc(sizeof(GameObject));
	if (gameObject == NULL) 
	{
		fprintf(stderr, "[Error] Failed to create game object '%s'", name);
		exit(1);
	}

	gameObject->id = ++idCounter;
	strcpy_s(gameObject->name, MAX_OBJECT_NAME_LEN, name);

	gameObject->components = NULL;
	gameObject->componentCount = 0;

    return gameObject;
}

void AddComponent(GameObject* targetObject, Component* component)
{
	ComponentListElement* newElement = malloc(sizeof(ComponentListElement));
	if (newElement == NULL)
	{
		fprintf(stderr, "[Error] Failed to add component");
		exit(1);
	}

	newElement->component = component;

	// Add element as new head
	newElement->next = targetObject->components;
	targetObject->components = newElement;

	// Increment component count
	++(targetObject->componentCount);

	// Bind component to game object
	BindComponent(component, targetObject);
}

Component* GetComponent(GameObject* gameObject, const char* componentName)
{
	// Compare names
	ComponentListElement* current = gameObject->components;
	while (current != NULL)
	{
		if (strcmp(componentName, GetComponentName(current->component)) == 0)
			return current->component;

		current = current->next;
	}

	return NULL;
}

char* GetGameObjectName(GameObject* gameObject)
{
	return gameObject->name;
}

void StartGameObject(GameObject* gameObject)
{
	// Start each component
	ComponentListElement* current = gameObject->components;
	while (current != NULL)
	{
		StartComponent(current->component);
		current = current->next;
	}
}

void UpdateGameObject(GameObject* gameObject, float deltaTime)
{
	// Update each component
	ComponentListElement* current = gameObject->components;
	while (current != NULL)
	{
		UpdateComponent(current->component, deltaTime);
		current = current->next;
	}
}

void RenderGameObject(GameObject* gameObject, Window* window)
{
	// Get render component
	Component* renderer = GetComponent(gameObject, "Renderer");
	if (renderer == NULL)
		return;

	RendererRender(renderer);
}
