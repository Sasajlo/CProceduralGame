#include "window.h"

#include <GL/glew.h> // OpenGL
#include <GLFW/glfw3.h> // Window and input

typedef struct Window
{
    char title[MAX_WINDOW_TITLE_LEN];
    int width;
    int height;
    GLFWwindow* window;
};

Window* CreateWindow(const char* title, int width, int height)
{
    // Initialize structure
    Window* window = malloc(sizeof(Window));
    if (window == NULL)
    {
        fprintf(stderr, "[Error] Failed to create window");
        exit(1);
    }

    strcpy_s(window->title, MAX_WINDOW_TITLE_LEN, title);
    window->width = width;
    window->height = height;

    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "[Error] Failed to initialize GLFW\n");
        exit(1);
    }
        
    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
    // Create a windowed mode window and its OpenGL context
    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window->window == NULL)
    {
        fprintf(stderr, "[Error] Failed to create glfw window\n");
        glfwTerminate();
        exit(1);
    }
        
    // Make the window's context current
    glfwMakeContextCurrent(window->window);
        
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "[Error] Failed to initialize GLEW\n");
        exit(1);
    }

    return window;
}

bool ShouldWindowClose(Window* window)
{
    return glfwWindowShouldClose(window->window);
}

void ClearWindow(Window* window)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void UpdateWindow(Window* window)
{
    //Swap front and back buffers
    glfwSwapBuffers(window->window);

    // Poll for and process events
    glfwPollEvents();
}

void CleanWindow(Window* window)
{
    if (window == NULL)
        return; // Nothing to clean

    // Free window
    free(window);
}

bool GetKey(Window* window, int keycode)
{
    return glfwGetKey(window->window, keycode);
}
