
#include "scene.h"

typedef struct ObjectListElement {
	GameObject* object;
	struct ObjectListElement* next;
} ObjectListElement;

struct Scene 
{
	Camera* mainCamera;
	ObjectListElement* objects;
	int objectCount;
};

struct SceneManager {
	Scene* scenes[MAX_SCENES];
	int sceneCount;
	int activeSceneIndex;
};

static SceneManager* sceneMagener = NULL;

Scene* CreateScene()
{
	Scene* scene = malloc(sizeof(Scene));
	if (scene == NULL) 
	{
		fprintf(stderr, "[Error] Failed to create scene");
		exit(1);
	}

	scene->objects = NULL;
	scene->objectCount = 0;

    return scene;
}

void SetMainCamera(Scene* scene, Camera* camera)
{
	scene->mainCamera = camera;
}

void AddObjectToScene(Scene* scene, GameObject* gameObject)
{
	ObjectListElement* newElement = malloc(sizeof(ObjectListElement));
	if (newElement == NULL)
	{
		fprintf(stderr, "[Error] Failed to add game object");
		exit(1);
	}

	newElement->object = gameObject;

	// Add element as new head
	newElement->next = scene->objects;
	scene->objects = newElement;

	// Increment object count
	++(scene->objectCount);
}

void StartScene(Scene* scene)
{
	// Start camera
	
	// Start each game object
	ObjectListElement* current = scene->objects;
	while (current != NULL)
	{
		StartGameObject(current->object);
		current = current->next;
	}
}

void UpdateScene(Scene* scene, float deltaTime)
{
	// Update each game object
	ObjectListElement* current = scene->objects;
	while (current != NULL)
	{
		UpdateGameObject(current->object, deltaTime);
		current = current->next;
	}

	// Update camera
	UpdateCamera(GetMainCamera());
}

void RenderScene(Scene* scene, Window* window)
{
	// Update each game object
	ObjectListElement* current = scene->objects;
	while (current != NULL)
	{
		RenderGameObject(current->object, window);
		current = current->next;
	}
}

void CleanScene(Scene* scene)
{
	if (scene == NULL)
		return; // Nothing to clean

	CleanCamera(scene->mainCamera);

	// Free scene
	free(scene);
}

void InitSceneManager()
{
	sceneMagener = (SceneManager*)malloc(sizeof(SceneManager));
	if (sceneMagener == NULL) 
	{
		fprintf(stderr, "[Error] Failed initialize scene manager");
		exit(1);
	}

	sceneMagener->sceneCount = 0;
	sceneMagener->activeSceneIndex = 0;
}

void AddScene(Scene* scene)
{
	if (sceneMagener->sceneCount == MAX_SCENES)
		return;

	sceneMagener->scenes[sceneMagener->sceneCount++] = scene;
}

Camera* GetMainCamera()
{
	if (sceneMagener->sceneCount == 0)
		return NULL;

	return sceneMagener->scenes[sceneMagener->activeSceneIndex]->mainCamera;
}
