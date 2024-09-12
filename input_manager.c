#include "input_manager.h"

struct InputManager {
	bool keyCurrentStates[GLFW_KEY_LAST + 1];
	bool keyPreviousStates[GLFW_KEY_LAST + 1];
};

static InputManager* inputManager = NULL;

void InitInputManager()
{
	inputManager = (InputManager*)malloc(sizeof(InputManager));
	if (inputManager == NULL)
	{
		fprintf(stderr, "[Error] Failed to initialize input manager");
		exit(1);
	}

	for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; i++) {
		inputManager->keyCurrentStates[i] = false;
		inputManager->keyPreviousStates[i] = false;
	}
}

void UpdateInput(Window* window)
{
	for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; i++) {
		inputManager->keyPreviousStates[i] = inputManager->keyCurrentStates[i];
		inputManager->keyCurrentStates[i] = GetKey(window, i);
	}
}

bool IsKeyDown(int keycode)
{
	return inputManager->keyCurrentStates[keycode] == true;
}

bool IsKeyPressed(int keycode)
{
	return inputManager->keyCurrentStates[keycode] == true && inputManager->keyPreviousStates[keycode] == false;
}

bool IsKeyReleased(int keycode)
{
	return inputManager->keyCurrentStates[keycode] == false && inputManager->keyPreviousStates[keycode] == true;
}
