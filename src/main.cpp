#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define WINDOW_TITLE "Real-Time Water Rendering"

using namespace glm;

GLFWwindow* window;

int CurrentWidth = 800;
int CurrentHeight = 600;

void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(GLFWwindow*, int, int);
void RenderFunction(void);

int main(int argc, char* argv[]) {

    Initialize(argc, argv);

    RenderFunction();
    
    exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]) {
    
    GLenum GlewInitResult;

    InitWindow(argc, argv);

    GlewInitResult = glewInit();

    //glewExperimental=true;

    if (GlewInitResult != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[]) {
    
    // Initialize GLFW
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initalize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(CurrentWidth, CurrentHeight, WINDOW_TITLE, NULL,
                              NULL);

    if(window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. Not a compatible\
                OpenGL 4.0 GPU\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, ResizeFunction);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void ResizeFunction(GLFWwindow* window, int Width, int Height) {
    glfwGetWindowSize(window, &Width, &Height);
    //CurrentWidth = Width;
    //CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
    glfwWindowShouldClose(window) == 0 );
}
