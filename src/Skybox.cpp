/**
 * @file Skybox.cpp
 * @author Samuel Gauthier
 */
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include "Skybox.h"

/**
 * @brief Creates a Skybox with the width @p width.
 *
 * @param width The width of the Skybox.
 */
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

/**
 * @brief Default Destructor.
 */
Skybox::~Skybox() {

    // Get the error information. Second call below to check that everything
    // went well.
    GLenum errorCheckValue = glGetError();

    // Disable the vertex attribute array.
    glDisableVertexAttribArray(0);

    // Unbind the vertex attribute buffer and delete it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->vertexBufferId);

    // Unbind the index attribute buffer and delete it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->indexBufferId);

    // Unbind the vertex array object and delete it.
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &this->vaoId);

    // Second error check.
    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not destroy the Skybox VBO: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Generates OpenGL vertex array and buffers.
 */
void Skybox::setup() {

    // Get the error information. Second call below to check that everything
    // went well.
    GLenum errorCheckValue = glGetError();

    // Fetch the sizes of the vertex and indices buffer.
    const size_t vertexBufferSize = this->vertices.size() * sizeof(GLfloat);
    const size_t indexBufferSize = this->indices.size() * sizeof(GLuint);

    // Generate the name for the vertex array object, and binds it.
    glGenVertexArrays(1, &this->vaoId);
    glBindVertexArray(this->vaoId);

    // Generate the vertex buffer object name, bind it, create and initialize
    // the vertex buffer object data store.
    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &this->vertices[0],
            GL_STATIC_DRAW);

    // Specify the location and data format of the vertex attribute at a custom
    // index to use when rendering.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Enable the vertex attribute array.
    glEnableVertexAttribArray(0);

    // Generate the index buffer object name, bind it, create and initialize
    // the index buffer object data store.
    glGenBuffers(1, &this->indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, &this->indices[0],
    GL_STATIC_DRAW);

    // Second error check.
    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR) {
        fprintf( stderr, "ERROR: Could not create a VBO for the skybox: %d \n",
                errorCheckValue);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Generates texture names and activates OpenGL texture unit with
 * custom properties given the six texture paths for each side of the
 * Skybox.
 *
 * @param front The front texture path.
 * @param back The back texture path.
 * @param top The top texture path.
 * @param bottom The bottom texture path.
 * @param left The left texture path.
 * @param right The right texture path.
 */
void Skybox::setupTexture(std::string front, std::string back, std::string top,
        std::string bottom, std::string left, std::string right) {

    // Generate a cube-map texture to hold all the sides
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->texture);

    // Load each image and copy it into a side of the cube-map texture
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

    // Set the texture parameters to repeat the texture in the three directions and
    // use the bi linear filtering when magnifying or reducing the textures.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

/**
 * @brief Returns true if the texture from the given file name could be
 * loaded and bound to the texture name. 
 *
 * @param texture The texture name.
 * @param side_target The side target of the Skybox.
 * @param file_name The texture path.
 *
 * @return True if the texture was loaded successfully, false otherwise.
 */
bool Skybox::loadCubeMapSide(GLuint texture, GLenum side_target, const char*
        file_name) {

    // Bind the texture to a cube map texturing target.
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    // Load the image from disk with the stb helper.
    int x, y, n;
    int force_channels = 4;
    unsigned char*  image_data = stbi_load(
            file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf(stderr, "ERROR: could not load %s\n", file_name);
        return false;
    }
    // Non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf(stderr,
                "WARNING: image %s is not power-of-2 dimensions\n",
                file_name);
    }

    // Copy image data into @p side_target of cube map
    glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            image_data);

    // Free the image pointer
    stbi_image_free(image_data);
    return true;
}

/**
 * @brief Issues the OpenGL draw call.
 */
void Skybox::draw() {

    // Disable the depth buffer to render the Skybox behind everything.
    glDepthMask(GL_FALSE);
    // Select an active texture unit and bind the cube map texture to it. Bind
    // the vertex array object and draws the vertices as indexed triangles on
    // the screen.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    glBindVertexArray(this->vaoId);
    glDrawElements(GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, NULL);
    // Reenable the depth buffer for the upcoming other objects to draw.
    glDepthMask(GL_TRUE);
}
