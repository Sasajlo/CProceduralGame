
#include "engine.h"
#include "scene.h"
#include "camera.h"
#include "game_object.h"
#include "component.h"
#include "player_component.h"
#include "transform_component.h"
#include "mesh_component.h"
#include "shader_component.h"
#include "renderer_component.h"
#include "texture_component.h"

int main() 
{
	// Create engine
	Engine* engine = CreateEngine("2D Game Engine", 1280, 720);

	// Create main sceene
	Scene* scene = CreateScene();
	SetActiveScene(engine, scene);

	// Create main camera
	Camera* camera = CreateCamera();
	SetMainCamera(scene, camera); // Set main camera in scene

// ***************************************************************************************************************

	// Create player object
	GameObject* playerObject = CreateGameObject("Player");

	// Add transform component
	Component* transformComponent = CreateTransformComponent();
	AddComponent(playerObject, transformComponent);

	// Set postion
	float* position = GetPosition(transformComponent);
	position[0] = -0.8f;
	position[1] = -0.8f;

	// Set scale
	float* scale = GetScale(transformComponent);
	scale[0] = 0.2f;
	scale[1] = 0.2f;

	// Add mesh component
	Component* meshComponent = CreateQuadMeshComponent();
	AddComponent(playerObject, meshComponent);

	// Create shader component
	Component* shaderComponent = CreateShaderComponent("shaders/mesh.vert", "shaders/mesh.frag");
	AddComponent(playerObject, shaderComponent);

	// Create texture component
	Component* textureComponent = CreateTextureComponent();
	LoadTexture(textureComponent, "images/player.png");
	AddComponent(playerObject, textureComponent);

	// Add renderer component
	Component* rendererComponent = CreateMeshRendererComponent();
	AddComponent(playerObject, rendererComponent);

	// Custom player component
	Component* playerComponent = CreatePlayerComponent();
	AddComponent(playerObject, playerComponent);

	// Add player object to the scene
	AddObjectToScene(scene, playerObject);

	// Set camera to follow the player
	SetCameraTarget(camera, playerObject);

// **************************************************************************************************************************************

	// Create second player object
	GameObject* player2Object = CreateGameObject("Player 2");

	// Add transform component
	Component* transform2Component = CreateTransformComponent();
	AddComponent(player2Object, transform2Component);

	// Set postion
	float* position2 = GetPosition(transform2Component);
	position2[0] = 0.0f;
	position2[1] = 0.0f;

	// Set scale
	float* scale2 = GetScale(transform2Component);
	scale2[0] = 0.5f;
	scale2[1] = 0.5f;

	// Add mesh component
	Component* mesh2Component = CreateQuadMeshComponent();
	AddComponent(player2Object, mesh2Component);

	// Create shader component
	Component* shader2Component = CreateShaderComponent("shaders/mesh.vert", "shaders/mesh.frag");
	AddComponent(player2Object, shader2Component);

	// Add renderer component
	Component* renderer2Component = CreateMeshRendererComponent();
	AddComponent(player2Object, renderer2Component);

	// Add player object to the scene
	AddObjectToScene(scene, player2Object);

// ******************************************************************************************************************************

	// Start game loop
	StartEngine(engine);

	// Clean
	CleanEngine(engine);

	return 0;
}