#pragma once

#include "common.h"
#include "camera.h"
#include "window.h"

typedef struct Scene Scene;
typedef struct SceneManager SceneManager;

Scene* CreateScene();
void SetMainCamera(Scene* scene, Camera* camera);
void AddObjectToScene(Scene* scene, GameObject* gameObject);
void StartScene(Scene* scene);
void UpdateScene(Scene* scene, float deltaTime);
void RenderScene(Scene* scene, Window* window);
void CleanScene(Scene* scene);

void InitSceneManager();
void AddScene(Scene* scene);
Camera* GetMainCamera();