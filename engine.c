#include "engine.h"
#include "window.h"
#include "input_manager.h"
#include "util.h"

#include "stb_image.h"

struct Engine 
{
	Window* window;
	Scene* activeScene;
	bool isRunning;
};

Engine* CreateEngine(const char* title, int width, int height)
{
	// Allocate memmory for engine
	Engine* engine = malloc(sizeof(Engine));
	if (engine == NULL) 
	{
		fprintf(stderr, "[Error] Failed to create engine");
		exit(1);
	}

	// Create window
	engine->window = CreateWindow(title, width, height);
	if (engine->window == NULL) 
	{
		fprintf(stderr, "[Error] Failed to create window");
		CleanEngine(engine);
		exit(1);
	}

	engine->activeScene = NULL;
	engine->isRunning = true;

	InitSceneManager();
	InitInputManager(engine->window);

    return engine;
}

void SetActiveScene(Engine* engine, Scene* scene)
{
	engine->activeScene = scene;
	AddScene(scene);

}

void StartEngine(Engine* engine)
{
// ------TEMP----------------------------------------------------------------------------------------------------
	// Load custom cursor image using stb_image
	int width, height, channels;
	unsigned char* image = stbi_load("images/crosshair.png", &width, &height, &channels, 0);
	if (!image) {
		printf("Failed to load cursor image\n");
		glfwTerminate();
		return -1;
	}

	// Create GLFWimage structure to hold image data
	GLFWimage glfw_image;
	glfw_image.width = width;
	glfw_image.height = height;
	glfw_image.pixels = image;

	// Create custom cursor
	GLFWcursor* cursor = glfwCreateCursor(&glfw_image, 0, 0);  // (0, 0) is the hotspot of the cursor
	if (!cursor) {
		printf("Failed to create custom cursor\n");
		stbi_image_free(image);
		glfwTerminate();
		return -1;
	}

	SetMouseCursor(engine->window, cursor);
// ------------------------------------------------------------------------------------------------------------


	// Randomize
	srand(GetTime());

	// Start scene
	StartScene(engine->activeScene);

	// Delta time
	ulong lastFrameTime = GetTime();

	while (!ShouldWindowClose(engine->window))
	{
		// Calculate delta time
		ulong currentTime = GetTime();
		float deltaTime = (float)(currentTime - lastFrameTime) / 1000.0f;
		lastFrameTime = currentTime;

		// Update keyboard input
		UpdateInput(engine->window);

		// Update active scene
		UpdateScene(engine->activeScene, deltaTime);

		// Render active scene
		ClearWindow(engine->window);
		RenderScene(engine->activeScene, engine->window);
		UpdateWindow(engine->window);
	}
}

void CleanEngine(Engine* engine)
{
	if (engine == NULL)
		return; // Nothing to clean

	// Clean window
	CleanWindow(engine->window);

	// Clean active scene
	CleanScene(engine->activeScene);

	// Clean engine
	free(engine);
}
