/**
 * @file Skybox.h
 * @author Samuel Gauthier
 */
#ifndef INCLUDED_SKYBOX
#define INCLUDED_SKYBOX

#include <vector>
#include <string>
#include <GL/glew.h>

/**
 * @brief Skybox with custom width and texture
 */
class Skybox {

    public:

        /**
         * @brief Default Skybox contructor.
         *
         * @param width The width of the skybox.
         */
        Skybox(GLfloat width);

        /**
         * @brief Default Destructor.
         */
        ~Skybox();

        /**
         * @brief Generates OpenGL vertex array and buffers. Needs to be called
         * before the draw() function.
         */
        void setup();

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
        void setupTexture(std::string front, std::string back, std::string top,
                std::string bottom, std::string left, std::string right);

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
        bool loadCubeMapSide(GLuint texture, GLenum side_target, const char*
                file_name);

        /**
         * @brief Draws the plane on the screen.
         */
        void draw();
        

    private:
        int indicesCount;
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        GLuint vaoId;
        GLuint vertexBufferId;
        GLuint indexBufferId;
        GLuint texture;

};

#endif /* ifndef INCLUDED_SKYBOX */
