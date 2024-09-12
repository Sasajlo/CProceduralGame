#include "input_manager.h"

struct InputManager {
	bool keyCurrentStates[GLFW_KEY_LAST + 1];
	bool keyPreviousStates[GLFW_KEY_LAST + 1];
    bool mouseCurrentState[2];
    bool mousePreviousState[2];
    float mousePosition[2];
};

static InputManager* inputManager = NULL;

// Mouse movement interupt
void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    inputManager->mousePosition[0] = xpos;
    inputManager->mousePosition[1] = ypos;
}

// Mouse button click interupt
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        printf("Left mouse button pressed\n");
        inputManager->mouseCurrentState[0] = true;
    }
    else
    {
        inputManager->mouseCurrentState[0] = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        inputManager->mouseCurrentState[1] = true;
        printf("Right mouse button pressed\n");
    }
    else
    {
        inputManager->mouseCurrentState[1] = false;
    }
}

void InitInputManager(Window* window)
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

    SetMouseCallbacks(window, mousePositionCallback, mouseButtonCallback);
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

float* GetMousePosition()
{
    return inputManager->mousePosition;
}
