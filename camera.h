#pragma once

#include "common.h"
#include "game_object.h"

typedef struct Camera Camera;

Camera* CreateCamera();
void SetCameraTarget(Camera* camera, GameObject* target);
void UpdateCamera(Camera* camera, float deltaTime);
float* GetCameraPosition(Camera* camera);
void CleanCamera(Camera* camera);