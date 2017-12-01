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

    indicesCount = indices.size();

    GLenum errorCheckValue = glGetError();

    const size_t vertexBufferSize = vertices.size() * sizeof(Vertex);
    const size_t vertexSize = sizeof(vertices[0]);
    const size_t rgbOffset = sizeof(vertices[0].XYZW);
    const size_t indexBufferSize = indices.size() * sizeof(GLuint);

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

Plane::~Plane() {

}
