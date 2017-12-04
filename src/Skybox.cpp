#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include "Skybox.h"

Skybox::Skybox(GLfloat width) {

    GLfloat vertices[] = {
        -width, -width, -width,
        width, -width, -width,
        width, -width,  width,
        -width, -width,  width,

        -width,  width, -width,
        width,  width, -width,
        width,  width,  width,
        -width,  width,  width
    };

    GLuint indices[] = {
        // bottom
        0, 2, 1,
        0, 3, 2,

        // top
        4, 5, 6,
        4, 6, 7,

        // back
        4, 1, 5,
        4, 0, 1,

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

    this->vertices.assign(vertices, vertices+24);
    this->indices.assign(indices, indices+36);
    this->indicesCount = this->indices.size();
}

Skybox::~Skybox() {
    GLenum errorCheckValue = glGetError();

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->vertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &this->vaoId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the Skybox VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Skybox::setup() {

    const size_t vertexBufferSize = this->vertices.size() * sizeof(GLfloat);
    const size_t indexBufferSize = this->indices.size() * sizeof(GLuint);

    GLenum errorCheckValue = glGetError();

    glGenVertexArrays(1, &this->vaoId);
    glBindVertexArray(this->vaoId);

    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &this->vertices[0],
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &this->indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, &this->indices[0],
    GL_STATIC_DRAW);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not create a VBO for the skybox: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Skybox::setupTexture(std::string front, std::string back, std::string top,
        std::string bottom, std::string left, std::string right) {

    // generate a cube-map texture to hold all the sides
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->texture);

    // load each image and copy into a side of the cube-map texture
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
            front.c_str());
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            back.c_str());
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            top.c_str());
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            bottom.c_str());
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            left.c_str());
    loadCubeMapSide(this->texture, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            right.c_str());

    // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

bool Skybox::loadCubeMapSide(GLuint texture, GLenum side_target,
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
    glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            image_data);
    free(image_data);
    return true;
}

void Skybox::draw() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    glBindVertexArray(this->vaoId);
    glDrawElements(GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, NULL);
    glDepthMask(GL_TRUE);
}
