#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"

#define WINDOW_TITLE "Real-Time Water Rendering"

using namespace glm;

struct Vertex {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
};

GLuint VertexShaderId;
GLuint FragmentShaderId;
GLuint ProgramId;
GLuint VaoId;
GLuint BufferId;
GLuint IndexBufferId;

GLFWwindow* window;

int CurrentWidth = 800;
int CurrentHeight = 600;

void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(GLFWwindow*, int, int);
void RenderFunction();
void Cleanup();
void CreateVBO();
void DestroyVBO();

int main(int argc, char* argv[]) {

    Initialize(argc, argv);

    RenderFunction();

    //Cleanup();
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

    ProgramId = LoadShaders("../src/vertex.vert",
            "../src/fragment.frag");

    CreateVBO();
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
    //glfwSetWindowSizeCallback(window, ResizeFunction);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void ResizeFunction(GLFWwindow* window, int Width, int Height) {

    glfwGetWindowSize(window, &Width, &Height);
    //CurrentWidth = Width;
    //CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ProgramId);

        //glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, 3*12, GL_UNSIGNED_BYTE, NULL);

		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

		//glDisableVertexAttribArray(1);
		//glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

	glDeleteProgram(ProgramId);

	glfwTerminate();
}

void CreateVBO() {

    Vertex vertices[] =
    {
        {{-1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{-0.33f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 0.33f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{-1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{-0.33f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 0.33f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{-0.33f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 0.33f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
    };

    GLubyte indices[] =
    {
        0, 4, 5,
        0, 5, 1,
        1, 5, 6,
        1, 6, 2,
        2, 6, 7,
        2, 7, 3,
        4, 8, 9,
        4, 9, 5,
        5, 9, 10,
        5, 10, 6,
        6, 10, 11,
        6, 11, 7,
    };

    GLenum errorCheckValue = glGetError();

    const size_t bufferSize = sizeof(vertices);
    const size_t vertexSize = sizeof(vertices[0]);
    const size_t rgbOffset = sizeof(vertices[0].XYZW);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, BufferId);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)
            rgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
            GL_STATIC_DRAW);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not create a VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }

}

void DestroyVBO() {

    GLenum errorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &BufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &IndexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Cleanup() {

    DestroyVBO();

    glDeleteProgram(ProgramId);
	glfwTerminate();
}
