#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include "Shader.h"

#define WINDOW_TITLE "Real-Time Water Rendering"

#define FRONT "../data/skybox/saint_lazarus_church/negz.jpg"
#define BACK "../data/skybox/saint_lazarus_church/posz.jpg"
#define TOP "../data/skybox/saint_lazarus_church/posy.jpg"
#define BOTTOM "../data/skybox/saint_lazarus_church/negy.jpg"
#define LEFT "../data/skybox/saint_lazarus_church/negx.jpg"
#define RIGHT "../data/skybox/saint_lazarus_church/posx.jpg"

using namespace glm;

struct Vertex {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
};

GLuint skyboxProgramId;
GLuint skyboxVaoId;
GLuint skyboxVertexBufferId;
GLuint skyboxIndexBufferId;
GLuint skyboxTexture;

GLuint programId;
GLuint vaoId;
GLuint bufferId;
GLuint indexBufferId;

GLuint matrixId;
GLuint skyboxVMatrixId;
GLuint skyboxPMatrixId;

GLFWwindow* window;

int windowWidth = 800;
int windowHeight = 600;

int HEIGHT = 20;
int WIDTH = 20;
int indicesCount = 0;
int skyboxIndicesCount = 0;

glm::mat4 mvp;
glm::mat4 v;
glm::mat4 p;


void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(GLFWwindow*, int, int);
void RenderFunction();
void Cleanup();
void CreateVBO();
void DestroyVBO();
void createMVP();
void createSkyBox();
void destroySkyBox();
void createCubeMap(const char* front, const char* back, const char* top, const
        char* bottom, const char* left, const char* right, GLuint* tex_cube);
bool loadCubeMapSide(GLuint texture, GLenum side_target, const char* file_name);

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

    //glewExperimental=true;

    if (GlewInitResult != GLEW_OK) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    skyboxProgramId = LoadShaders("../src/skybox.vert", "../src/skybox.frag");
    programId = LoadShaders("../src/vertex.vert", "../src/fragment.frag");

    createSkyBox();
    CreateVBO();

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
    //glfwSetWindowSizeCallback(window, ResizeFunction);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void ResizeFunction(GLFWwindow* window, int Width, int Height) {

    glfwGetWindowSize(window, &Width, &Height);
    //windowWidth = Width;
    //windowHeight = Height;
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
    glEnable( GL_DEPTH_TEST ); // enable depth-testing
    glDepthFunc( GL_LESS );		 // depth-testing interprets a smaller value as
                                 //"closer"
	glEnable( GL_CULL_FACE );	// cull face
	glCullFace( GL_BACK );		 // cull back face
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //glUseProgram(skyboxProgramId);
        //glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
        //glDrawElements(GL_LINE, skyboxIndicesCount, GL_UNSIGNED_INT, NULL);

        // Render the skybox
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDepthMask(GL_FALSE);
        glUseProgram(skyboxProgramId);

        //glUniformMatrix4fv(skyboxVMatrixId, 1, GL_FALSE, &v[0][0]);
        //glUniformMatrix4fv(skyboxPMatrixId, 1, GL_FALSE, &p[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glBindVertexArray(skyboxVaoId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);

        // Render the plane
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(programId);

        glBindVertexArray(vaoId);
        //glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

	//glDeleteProgram(programId);

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

    //printf("size of vertices: %li\n", vertexBufferSize);
    //printf("size of indices: %li\n", indexBufferSize);
    //printf("last element of indexed array: %u\n", indices.back());

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &vertices[0],
            GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)
            rgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
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
    glDeleteBuffers(1, &bufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vaoId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Cleanup() {

    DestroyVBO();
    destroySkyBox();

    glDeleteProgram(programId);
	glfwTerminate();
}

void createMVP() {

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)
            windowWidth / (float) windowHeight, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(glm::vec3(-2, -2, 3), glm::vec3(0, 0, 0),
            glm::vec3(0, 0, 1));
    //glm::mat4 view = glm::lookAt(glm::vec3(1, 1, 0), glm::vec3(0, 0, 0),
    //        glm::vec3(0, 1, 0));

    glm::mat4 model = glm::mat4(1.0f);

    v = view;
    p = projection;

    skyboxVMatrixId = glGetUniformLocation(skyboxProgramId, "V");
    skyboxPMatrixId = glGetUniformLocation(skyboxProgramId, "P");

    mvp = projection * view * model;

    matrixId = glGetUniformLocation(programId, "mvp");
}

void createSkyBox() {
    float points[] = {
        -10.0f,  10.0f, -10.0f,
        -10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,

        -10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,

        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,

        -10.0f, -10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,

        -10.0f,  10.0f, -10.0f,
        10.0f,  10.0f, -10.0f,
        10.0f,  10.0f,  10.0f,
        10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f, -10.0f,

        -10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
        10.0f, -10.0f, -10.0f,
        10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
        10.0f, -10.0f,  10.0f
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    skyboxVaoId = vao;

    createCubeMap(FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT, &skyboxTexture);
    //GLfloat vertices[] = {
    //    -10.0f, -10.0f, -10.0f,
    //     10.0f, -10.0f, -10.0f,
    //     10.0f, -10.0f,  10.0f,
    //    -10.0f, -10.0f,  10.0f,

    //    -10.0f,  10.0f, -10.0f,
    //     10.0f,  10.0f, -10.0f,
    //     10.0f,  10.0f,  10.0f,
    //    -10.0f,  10.0f,  10.0f,
    //};
    /*
    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
    };

    GLuint indices[] = {
        // bottom
        0, 2, 1,
        0, 3, 2,

        // top
        4, 5, 6,
        4, 6, 7,

        // back
        //4, 1, 5,
        5, 4, 1,
        4, 0, 1,
        //4, 0, 1,

        // left
        5, 2, 6,
        5, 1, 2,

        // front
        6, 3, 7,
        6, 2, 3,

        // right
        7, 0, 4,
        7, 3, 0
    };

    skyboxIndicesCount = 36;

    const size_t vertexBufferSize = sizeof(vertices);
    const size_t indexBufferSize = sizeof(indices);

    GLenum errorCheckValue = glGetError();

    glGenVertexArrays(1, &skyboxVaoId);
    glBindVertexArray(skyboxVaoId);

    glGenBuffers(1, &skyboxVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &skyboxIndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxIndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indices,
    GL_STATIC_DRAW);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not create a VBO for the skybox: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
    */
}

void destroySkyBox() {
    GLenum errorCheckValue = glGetError();

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &skyboxVertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &skyboxIndexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &skyboxVaoId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void createCubeMap(const char* front, const char* back, const char* top, const
        char* bottom, const char* left, const char* right, GLuint* tex_cube) {
    // generate a cube-map texture to hold all the sides
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, tex_cube);
    
    // load each image and copy into a side of the cube-map texture
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
    loadCubeMapSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
    // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
bool loadCubeMapSide(GLuint texture, GLenum side_target,
        const char* file_name) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int x, y, n;
    int force_channels = 4;
    unsigned char*  image_data = stbi_load(
            file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf(stderr, "ERROR: could not load %s\n", file_name);
        return false;
    }
    // non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf(stderr,
                "WARNING: image %s is not power-of-2 dimensions\n",
                file_name);
    }

    // copy image data into 'target' side of cube map
    glTexImage2D(
            side_target,
            0,
            GL_RGBA,
            x,
            y,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image_data);
    free(image_data);
    return true;
}
