/**
 * @file main.cpp
 * @brief Main function of the rtwr application
 * @author Samuel Gauthier
 */
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Shader.h"
#include "Skybox.h"
#include "Plane.h"
#include "FPSCounter.h"
#include "Camera.h"

#define WINDOW_TITLE "Real-Time Water Rendering"

// Select the skybox
#define SKYBOX_NAME "san_francisco"

// Define the image paths of the skybox and the normal map.
#define FRONT "../data/skybox/" SKYBOX_NAME "/front.jpg"
#define BACK "../data/skybox/" SKYBOX_NAME "/back.jpg"
#define UP "../data/skybox/" SKYBOX_NAME "/up.jpg"
#define DOWN "../data/skybox/" SKYBOX_NAME "/down.jpg"
#define LEFT "../data/skybox/" SKYBOX_NAME "/left.jpg"
#define RIGHT "../data/skybox/" SKYBOX_NAME "/right.jpg"

#define NORMAL_MAP "../data/normal_map.jpg"

// Shader program Ids
GLuint skyboxProgramId;
GLuint waterProgramId;

// Model, view, projection and time Ids
GLuint waterMMatrixId;
GLuint waterVMatrixId;
GLuint waterPMatrixId;
GLuint skyboxVMatrixId;
GLuint skyboxPMatrixId;
GLuint timeId;

// Window handle pointer
GLFWwindow* window;

// Model, view and projection matrices.
glm::mat4 m;
glm::mat4 v;
glm::mat4 p;

// Application window width and height
int windowWidth = 800;
int windowHeight = 600;

// Camera setup
glm::vec3 position = glm::vec3(0, 3, 3);
glm::vec3 target = glm::vec3(0, 0, 0);
glm::vec3 up = glm::vec3(0, 1, 0);
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)
        windowWidth / (float) windowHeight, 0.1f, 100.0f);
Camera camera = Camera(position, target, up, projection);

// Plane setup
const int HEIGHT = 4;
const int WIDTH = 4;
glm::vec2 waterResolution = glm::vec2(30, 30);
Plane plane = Plane(WIDTH, HEIGHT, target, waterResolution);

// Skybox and FPSCounter setup
Skybox skybox = Skybox(10.0f);
FPSCounter counter = FPSCounter();

// Mouse state and positions
int mouseState;
bool mouseButtonLeftDown = false;
bool mouseButtonRightDown = false;
double previousX;
double previousY;

/**
 * @brief 
 */
void Initialize();

/**
 * @brief 
 */
void InitWindow();

/**
 * @brief 
 *
 * @param GLFWwindow
 * @param int
 * @param int
 */
void resizeFunction(GLFWwindow*, int, int);

/**
 * @brief 
 *
 * @param window
 * @param xOffset
 * @param yOffset
 */
void trackScroll(GLFWwindow* window, double xOffset, double yOffset);

/**
 * @brief 
 *
 * @param window
 * @param xPos
 * @param yPos
 */
void trackMousePosition(GLFWwindow* window, double xPos, double yPos);

/**
 * @brief 
 *
 * @param window
 * @param button
 * @param action
 * @param mods
 */
void trackMouseButton(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief Renders the skybox and the plane. Contains the main rendering loop.
 */
void RenderFunction();

/**
 * @brief 
 */
void Cleanup();

/**
 * @brief Create the model view 
 */
void createMVP();

/**
 * @brief 
 */
void updateMVP();

/**
 * @brief Main function
 *
 * @param argc The command line argument count.
 * @param argv[] The command line argument values
 *
 * @return 
 */
int main(int argc, char* argv[]) {

    // Initialize GLFW, window, GLEW, skybox and plane.
    Initialize();

    // Render the skybox and the plane.
    RenderFunction();

    // Delete shaders and terminate the GLFW library
    Cleanup();
    exit(EXIT_SUCCESS);
}

/**
 * @brief Initialize the wind
 */
void Initialize() {

    GLenum GlewInitResult;

    InitWindow();

    GlewInitResult = glewInit();

    if (GlewInitResult != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Load the shaders
    skyboxProgramId = LoadShaders("../src/skybox.vert", "../src/skybox.frag");
    waterProgramId = LoadShaders("../src/water.vert", "../src/water.frag");

    skybox.setup();
    skybox.setupTexture(FRONT, BACK, UP, DOWN, LEFT, RIGHT);
    plane.setup();
    plane.setupTexture(NORMAL_MAP);

    createMVP();
    timeId = glGetUniformLocation(waterProgramId, "t");
}

/**
 * @brief Initializes the GLFW library, creates the window and sets the GLFW
 * callbacks.
 */
void InitWindow() {

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

    window = glfwCreateWindow(windowWidth, windowHeight, WINDOW_TITLE, NULL,
            NULL);

    if(window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. Not a compatible\
                OpenGL 4.0 GPU\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    // Set the different callbacks
    glfwSetWindowSizeCallback(window, resizeFunction);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetScrollCallback(window, trackScroll);
    glfwSetCursorPosCallback(window, trackMousePosition);
    glfwSetMouseButtonCallback(window, trackMouseButton);
}

void resizeFunction(GLFWwindow* window, int Width, int Height) {

    glfwGetWindowSize(window, &Width, &Height);
    windowWidth = Width;
    windowHeight = Height;
    updateMVP();
    glViewport(0, 0, windowWidth, windowHeight);
}

/**
 * @brief Mouse wheel callback function for GLFW. Tracks the wheel scroll in the
 * y direction and updates the camera zoom accordingly.
 *
 * @param window The window
 * @param xOffset The x offset
 * @param yOffset The y offset
 */
void trackScroll(GLFWwindow* window, double xOffset, double yOffset) {

    camera.zoom(yOffset);
    updateMVP();
}

/**
 * @brief Mouse position callback function for GLFW. Tracks the x and y
 * positions and updates the camera if the user interacts with the window.
 *
 * @param window The window
 * @param xPos The x position relative to the window of the cursor.
 * @param yPos The y position relative to the window of the cursor.
 */
void trackMousePosition(GLFWwindow* window, double xPos, double yPos) {

    if(mouseButtonLeftDown) {

        float dPhi = (float)(previousX - xPos) / 300;
        float dTheta = (float)(previousY - yPos) / 300;

        camera.rotate(dPhi, dTheta);
        updateMVP();

        previousX = xPos;
        previousY = yPos;
    }

    else if(mouseButtonRightDown) {

        float dx = (float)(previousX - xPos) / 200;
        float dy = (float)(previousY - yPos) / 200;

        camera.pan(dx, dy);
        updateMVP();

        previousX = xPos;
        previousY = yPos;
    }
}

/**
 * @brief Mouse button callback function for GLFW. Tracks the clicks and their
 * position.
 *
 * @param window The window.
 * @param button The mouse button.
 * @param action The button action.
 * @param mods The modifier bits.
 */
void trackMouseButton(GLFWwindow* window, int button, int action, int mods) {

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        glfwGetCursorPos(window, &previousX, &previousY);
        mouseButtonLeftDown = true;
    }

    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

        mouseButtonLeftDown = false;
    }

    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

        glfwGetCursorPos(window, &previousX, &previousY);
        mouseButtonRightDown = true;
    }

    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {

        mouseButtonRightDown = false;
    }
}

/**
 * @brief Renders the skybox and the plane. Contains the main rendering loop.
 */
void RenderFunction() {

    // Specify the model, view and projection matrices to the skybox and water
    // shader programs. For the water program additionally provide the normal
    // map.
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    glUseProgram(waterProgramId);
    glUniformMatrix4fv(waterMMatrixId, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(waterVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(waterPMatrixId, 1, GL_FALSE, &p[0][0]);
    glUniform1i(glGetUniformLocation(waterProgramId, "normalMap"), 1);

    // Prepare for rendering
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Fill the front and back faces of polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Enable the depth comparisons with the depth buffer
    glEnable(GL_DEPTH_TEST);
    // Specify the function used for depth buffer comparisons.
    glDepthFunc(GL_LESS);
    // Enable 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glEnable(GL_MULTISAMPLE);

    do {
        counter.update();
        // Clear the color and depth buffers to avoid artifacts
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Install the skybox shader object as part of the current rendering
        // state.
        glUseProgram(skyboxProgramId);
        // Draw the skybox
        skybox.draw();

        // Install the water shader object as part of the current rendering
        // state.
        glUseProgram(waterProgramId);
        // Specify the value to use for the timer
        glUniform1f(timeId, counter.getCurrentTime());
        // Draw the plane.
        plane.draw();

        // Swap buffers
        glfwSwapBuffers(window);
        // Process the pending events
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

	glfwTerminate();
}

/**
 * @brief Delete the plane and skybox shader program objects and terminate the
 * GLFW library.
 */
void Cleanup() {

    glDeleteProgram(waterProgramId);
    glDeleteProgram(skyboxProgramId);
	glfwTerminate();
}

/**
 * @brief Create the model, view and projection matrices from the camera and
 * get the location of the corresponding uniform variables from the water and
 * skybox shaders.
 */
void createMVP() {

    m = glm::mat4(1.0f);
    v = camera.getViewMatrix();
    p = camera.getProjectionMatrix();

    skyboxVMatrixId = glGetUniformLocation(skyboxProgramId, "V");
    skyboxPMatrixId = glGetUniformLocation(skyboxProgramId, "P");

    waterMMatrixId = glGetUniformLocation(waterProgramId, "M");
    waterVMatrixId = glGetUniformLocation(waterProgramId, "V");
    waterPMatrixId = glGetUniformLocation(waterProgramId, "P");

}

/**
 * @brief Specify the updated model view and projection matrices to the water
 * and skybox shaders.
 */
void updateMVP() {

    // Discard the rotation for the skybox
    v = glm::mat4(glm::mat3(camera.getViewMatrix()));
    p = camera.getProjectionMatrix();

    // Specify the updated view and projection matrices to the skybox shader
    // program. 
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    // Fetch the full view matrix from the camera.
    v = camera.getViewMatrix();

    // Specify the updated model, view and projection matrices to the skybox
    // shader program. 
    glUseProgram(waterProgramId);
    glUniformMatrix4fv(waterMMatrixId, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(waterVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(waterPMatrixId, 1, GL_FALSE, &p[0][0]);
}
