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

int HEIGHT = 50;
int WIDTH = 50;
int indicesCount = 0;

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

        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);

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

    // Height and width specified in amount of vertices
    int height = HEIGHT;
    int width = WIDTH;
    // Total triangle: (height * width) - 2

    float heightRatio = 2.0/(height-1);
    float widthRatio = 2.0/(width-1);

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Vertex k = {{i*widthRatio - 1.0f, j*heightRatio - 1.0f, 0.0f, 1.0f},
                {0.0f, 1.0f, 0.0f, 0.0f}};
            vertices.push_back(k);
        }
    }

    for (int j = 0; j < ( height-1 ) ; j++) {
        for (int i = 0; i < ( width-1 ); i++) {
            // *-*
            //  \|
            //   *
            indices.push_back(j*width + i);
            indices.push_back((j+1)*width + (i+1));
            indices.push_back(j*width + (i+1));

            // *
            // |\
            // *-*
            indices.push_back(j*width + i);
            indices.push_back((j+1)*width + i);
            indices.push_back((j+1)*width + (i+1));
        }
    }

    indicesCount = indices.size();

    GLenum errorCheckValue = glGetError();

    const size_t vertexBufferSize = vertices.size() * sizeof(Vertex);
    const size_t vertexSize = sizeof(vertices[0]);
    const size_t rgbOffset = sizeof(vertices[0].XYZW);
    const size_t indexBufferSize = indices.size() * sizeof(GLuint);

    printf("size of vertices: %li\n", vertexBufferSize);
    printf("size of indices: %li\n", indexBufferSize);
    printf("last element of indexed array: %u\n", indices.back());

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, BufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &vertices[0],
            GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)
            rgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize,
            &indices[0], GL_STATIC_DRAW);

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
