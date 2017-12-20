#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//#define STB_IMAGE_IMPLEMENTATION 
//#include "stb_image.h"

#include "Shader.h"
#include "Skybox.h"
#include "Plane.h"
#include "FPSCounter.h"
#include "Camera.h"

#define WINDOW_TITLE "Real-Time Water Rendering"

#define FRONT "../data/skybox/saint_lazarus_church/negz.jpg"
#define BACK "../data/skybox/saint_lazarus_church/posz.jpg"
#define TOP "../data/skybox/saint_lazarus_church/posy.jpg"
#define BOTTOM "../data/skybox/saint_lazarus_church/negy.jpg"
#define LEFT "../data/skybox/saint_lazarus_church/negx.jpg"
#define RIGHT "../data/skybox/saint_lazarus_church/posx.jpg"

using namespace glm;

GLuint skyboxProgramId;
GLuint waterProgramId;

GLuint waterMMatrixId;
GLuint waterVMatrixId;
GLuint waterPMatrixId;
GLuint skyboxVMatrixId;
GLuint skyboxPMatrixId;
GLuint timeId;

GLFWwindow* window;

int windowWidth = 800;
int windowHeight = 600;

int HEIGHT = 50;
int WIDTH = 50;

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)
        windowWidth / (float) windowHeight, 0.1f, 100.0f);

glm::vec3 position = glm::vec3(0, 3, 3);
glm::vec3 target = glm::vec3(0, 0, 0);
glm::vec3 up = glm::vec3(0, 1, 0);

glm::mat4 m;
glm::mat4 v;
glm::mat4 p;

Skybox skybox = Skybox(10.0f);
Plane plane = Plane(WIDTH, HEIGHT);
FPSCounter counter = FPSCounter();
Camera camera = Camera(position, target, up, projection);

int mouseState;
bool mouseDown = false;
double previousX;
double previousY;

void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(GLFWwindow*, int, int);
void trackScroll(GLFWwindow* window, double xOffset, double yOffset);
void trackMousePosition(GLFWwindow* window, double xPos, double yPos);
void trackMouseButton(GLFWwindow* window, int button, int action, int mods);
void RenderFunction();
void Cleanup();
void createMVP();
void updateMVP();

int main(int argc, char* argv[]) {

    Initialize(argc, argv);

    RenderFunction();

    Cleanup();
    exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]) {

    GLenum GlewInitResult;

    InitWindow(argc, argv);

    GlewInitResult = glewInit();

    if (GlewInitResult != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    skyboxProgramId = LoadShaders("../src/skybox.vert", "../src/skybox.frag");
    waterProgramId = LoadShaders("../src/water.vert", "../src/water.frag");

    skybox.setup();
    skybox.setupTexture(FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT);
    plane.setup();

    createMVP();
    timeId = glGetUniformLocation(waterProgramId, "t");
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

    window = glfwCreateWindow(windowWidth, windowHeight, WINDOW_TITLE, NULL,
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
    glfwSetScrollCallback(window, trackScroll);
    glfwSetCursorPosCallback(window, trackMousePosition);
    glfwSetMouseButtonCallback(window, trackMouseButton);
}

void ResizeFunction(GLFWwindow* window, int Width, int Height) {

    glfwGetWindowSize(window, &Width, &Height);
    windowWidth = Width;
    windowHeight = Height;
    updateMVP();
    glViewport(0, 0, windowWidth, windowHeight);
}

void trackScroll(GLFWwindow* window, double xOffset, double yOffset) {

    camera.zoom(yOffset);
    updateMVP();
}

void trackMousePosition(GLFWwindow* window, double xPos, double yPos) {

    if(mouseDown) {

        float dPhi = (float)(previousX - xPos) / 300;
        float dTheta = (float)(previousY - yPos) / 300;

        camera.rotate(dPhi, dTheta);
        updateMVP();

        previousX = xPos;
        previousY = yPos;
    }
}

void trackMouseButton(GLFWwindow* window, int button, int action, int mods) {

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &previousX, &previousY);
        mouseDown = true;
    }

    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseDown = false;
    }


}

void RenderFunction() {

    // Send matrices
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    glUseProgram(waterProgramId);
    glUniformMatrix4fv(waterMMatrixId, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(waterVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(waterPMatrixId, 1, GL_FALSE, &p[0][0]);

    // Prepare rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glEnable(GL_MULTISAMPLE);

    do {
        counter.update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the skybox
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDepthMask(GL_FALSE);
        glUseProgram(skyboxProgramId);
        skybox.draw();

        // Render the plane
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDepthMask(GL_TRUE);
        glUseProgram(waterProgramId);
        glUniform1f(timeId, counter.getCurrentTime());
        plane.draw();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

	glfwTerminate();
}

void Cleanup() {

    glDeleteProgram(waterProgramId);
    glDeleteProgram(skyboxProgramId);
	glfwTerminate();
}

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

void updateMVP() {

    // Discard the rotation for the skybox
    v = glm::mat4(glm::mat3(camera.getViewMatrix()));
    p = camera.getProjectionMatrix();

    // Send matrices
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    v = camera.getViewMatrix();

    glUseProgram(waterProgramId);
    glUniformMatrix4fv(waterMMatrixId, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(waterVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(waterPMatrixId, 1, GL_FALSE, &p[0][0]);
}
