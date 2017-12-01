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

#define WINDOW_TITLE "Real-Time Water Rendering"

#define FRONT "../data/skybox/saint_lazarus_church/negz.jpg"
#define BACK "../data/skybox/saint_lazarus_church/posz.jpg"
#define TOP "../data/skybox/saint_lazarus_church/posy.jpg"
#define BOTTOM "../data/skybox/saint_lazarus_church/negy.jpg"
#define LEFT "../data/skybox/saint_lazarus_church/negx.jpg"
#define RIGHT "../data/skybox/saint_lazarus_church/posx.jpg"

using namespace glm;

GLuint skyboxProgramId;
//GLuint skyboxVaoId;
//GLuint skyboxVertexBufferId;
//GLuint skyboxIndexBufferId;
//GLuint skyboxTexture;

GLuint programId;
//GLuint vaoId;
//GLuint bufferId;
//GLuint indexBufferId;

GLuint matrixId;
GLuint skyboxVMatrixId;
GLuint skyboxPMatrixId;

GLFWwindow* window;

int windowWidth = 800;
int windowHeight = 600;

int HEIGHT = 50;
int WIDTH = 50;
//int indicesCount = 0;
//int skyboxIndicesCount = 0;

glm::mat4 mvp;
glm::mat4 v;
glm::mat4 p;

Skybox skybox = Skybox(10.0f);
Plane plane = Plane(WIDTH, HEIGHT);

void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(GLFWwindow*, int, int);
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
    programId = LoadShaders("../src/vertex.vert", "../src/fragment.frag");

    skybox.setup();
    skybox.setupTexture(FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT);
    plane.setup();

    createMVP();
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
}

void ResizeFunction(GLFWwindow* window, int Width, int Height) {

    glfwGetWindowSize(window, &Width, &Height);
    windowWidth = Width;
    windowHeight = Height;
    updateMVP();
    glViewport(0, 0, windowWidth, windowHeight);
}

void RenderFunction() {

    // Send matrices
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    glUseProgram(programId);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

    // Prepare rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST );
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the skybox
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDepthMask(GL_FALSE);
        glUseProgram(skyboxProgramId);
        skybox.draw();

        // Render the plane
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(programId);
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

    glDeleteProgram(programId);
    glDeleteProgram(skyboxProgramId);
	glfwTerminate();
}

void createMVP() {

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)
            windowWidth / (float) windowHeight, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 1, -3), glm::vec3(0, 0, 0),
            glm::vec3(0, 0, 1));
    glm::mat4 model = glm::mat4(1.0f);

    v = view;
    p = projection;

    skyboxVMatrixId = glGetUniformLocation(skyboxProgramId, "V");
    skyboxPMatrixId = glGetUniformLocation(skyboxProgramId, "P");

    mvp = projection * view * model;

    matrixId = glGetUniformLocation(programId, "mvp");
}

void updateMVP() {

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)
            windowWidth / (float) windowHeight, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(glm::vec3(0, 1, -3), glm::vec3(0, 0, 0),
            glm::vec3(0, 0, 1));
    
    glm::mat4 model = glm::mat4(1.0f);

    v = view;
    p = projection;
    mvp = projection * view * model;

    // Send matrices
    glUseProgram(skyboxProgramId);
    glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
    glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

    glUseProgram(programId);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
}
