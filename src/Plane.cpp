/**
 * @file Plane.cpp
 * @brief Plane class
 * @author Samuel Gauthier
 */
#include "stb_image.h"
#include "Plane.h"

/**
 * @brief Default constructor for the Plane class. Creates a plane centered
 * around \p center with a \p width and \p height in model coordinates and with
 * a \p resolution in vertex size.
 *
 * @param width The width in model coordinates. Default value: 2
 * @param height The height in model coordinates. Default value: 2
 * @param center The center in model coordinates. Default value: 0, 0, 0
 * @param resolution The resolution in vertex. Default value: 20, 20
 */
Plane::Plane(int width, int height, glm::vec3 center, glm::vec2 resolution) :
    width{width}, height{height}, center{center}, resolution{resolution} {

    float rH = this->resolution.y;
    float rW = this->resolution.x;
    float heightRatio = this->height/(rH-1);
    float widthRatio = this->width/(rW-1);
    float dH = this->height/2;
    float dW = this->width/2;

    for (int j = 0; j < rH; j++) {
        for (int i = 0; i < rW; i++) {
            Vertex k = {{this->center.x + i*widthRatio - dW, this->center.y,
                this->center.z + j*heightRatio - dH, 1.0f},
                {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}};
            this->vertices.push_back(k);
        }
    }

    for (int j = 0; j < ( rH-1 ) ; j++) {
        for (int i = 0; i < ( rW-1 ); i++) {
            // a-c
            // |/ 
            // b
            this->indices.push_back(j*rW + i);
            this->indices.push_back((j+1)*rW + (i));
            this->indices.push_back(j*rW + (i+1));

            //   a
            //  /|
            // b-c
            this->indices.push_back(j*rW + (i+1));
            this->indices.push_back((j+1)*rW + i);
            this->indices.push_back((j+1)*rW + (i+1));
        }
    }

    this->indicesCount = this->indices.size();
}

/**
 * @brief Destructor
 */
Plane::~Plane() {

    GLenum errorCheckValue = glGetError();

    glDisableVertexAttribArray(2);
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

/**
 * @brief Generates OpenGL vertex array and buffers
 */
void Plane::setup() {

    GLenum errorCheckValue = glGetError();

    const size_t vertexBufferSize = this->vertices.size() * sizeof(Vertex);
    const size_t vertexSize = sizeof(this->vertices[0]);
    const size_t rgbOffset = sizeof(this->vertices[0].XYZW);
    const size_t normalOffset = sizeof(this->vertices[0].XYZW) +
        sizeof(this->vertices[0].RGBA);
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
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)
            normalOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

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

/**
 * @brief Generates texture name and activates OpenGL texture unit with
 * custom properties given a texture path.
 *
 * @param texturePath The texture path
 */
void Plane::setupTexture(std::string texturePath) {

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &this->normalTexture);

    loadTexture(this->normalTexture, texturePath.c_str());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

/**
 * @brief Returns true if the texture from the given file name could be
 * loaded and bound to the texture name.
 *
 * @param texture The texture name
 * @param file_name The file name
 *
 * @return True if the texture was loaded successfully, false otherwise.
 */
bool Plane::loadTexture(GLuint texture, const char* file_name) {

    glBindTexture(GL_TEXTURE_2D, texture);

    int x, y, n;
    int force_channels = 3;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE,
            image_data);

    stbi_image_free(image_data);
    return true;
}

/**
 * @brief Issues the OpenGL draw call
 */
void Plane::draw() {

    glBindVertexArray(this->vaoId);
    glDrawElements(GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, NULL);
}
