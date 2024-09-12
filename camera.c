
#include "camera.h"
#include "game_object.h"
#include "transform_component.h"
#include "math2.h"

#define LERP_SPEED 2.5f

struct Camera 
{
	float position[3];
	GameObject* target;
};

Camera* CreateCamera()
{
	Camera* camera = malloc(sizeof(Camera));
	if (camera == NULL) 
	{
		fprintf(stderr, "[Error] Failed to create camera");
		exit(1);
	}
	camera->target = NULL;
	camera->position[0] = 0.0f;
	camera->position[1] = 0.0f;
	camera->position[2] = 0.0f;

	return camera;
}

void SetCameraTarget(Camera* camera, GameObject* target)
{
	camera->target = target;
}

void UpdateCamera(Camera* camera, float deltaTime)
{
	if (camera == NULL)
		return;

	if (camera->target == NULL)
		return;

	Component* transformComponent = GetComponent(camera->target, "Transform");
	if (transformComponent == NULL)
		return;

	float* targetPosition = GetPosition(transformComponent);
	camera->position[0] = Lerp(camera->position[0], targetPosition[0], LERP_SPEED * deltaTime);
	camera->position[1] = Lerp(camera->position[1], targetPosition[1], LERP_SPEED * deltaTime);
	camera->position[2] = Lerp(camera->position[2], targetPosition[2], LERP_SPEED * deltaTime);
}

float* GetCameraPosition(Camera* camera)
{
	return camera->position;
}

void CleanCamera(Camera* camera)
{
	if (camera == NULL)
		return; // Nothing to clean

	// Free camera
	free(camera);
}
