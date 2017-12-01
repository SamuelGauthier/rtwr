#include "Plane.h"

Plane::Plane(int width, int height) : width{width}, height{height} {
    float heightRatio = 2.0/(height-1);
    float widthRatio = 2.0/(width-1);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Vertex k = {{j*heightRatio - 1.0f, 0.0f, i*widthRatio - 1.0f, 1.0f},
                {0.0f, 1.0f, 0.0f, 0.0f}};
            this->vertices.push_back(k);
        }
    }

    for (int j = 0; j < ( height-1 ) ; j++) {
        for (int i = 0; i < ( width-1 ); i++) {
            // *-*
            //  \|
            //   *
            this->indices.push_back(j*width + i);
            this->indices.push_back((j+1)*width + (i+1));
            this->indices.push_back(j*width + (i+1));

            // *
            // |\
            // *-*
            this->indices.push_back(j*width + i);
            this->indices.push_back((j+1)*width + i);
            this->indices.push_back((j+1)*width + (i+1));
        }
    }

    indicesCount = this->indices.size();
}

Plane::~Plane() {

    GLenum errorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->vertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &this->vaoId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Plane::setup() {

    GLenum errorCheckValue = glGetError();

    const size_t vertexBufferSize = this->vertices.size() * sizeof(Vertex);
    const size_t vertexSize = sizeof(this->vertices[0]);
    const size_t rgbOffset = sizeof(this->vertices[0].XYZW);
    const size_t indexBufferSize = this->indices.size() * sizeof(GLuint);

    glGenVertexArrays(1, &this->vaoId);
    glBindVertexArray(this->vaoId);

    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &this->vertices[0],
            GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)
            rgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &this->indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize,
            &this->indices[0], GL_STATIC_DRAW);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not create a VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

void Plane::draw() {

    glBindVertexArray(this->vaoId);
    glDrawElements(GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, NULL);
}
