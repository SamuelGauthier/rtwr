#ifndef INCLUDED_SKYBOX
#define INCLUDED_SKYBOX

#include <vector>
#include <string>
#include <GL/glew.h>

class Skybox {

    public:
        Skybox(GLfloat width);
        ~Skybox();
        void setup();
        void setupTexture(std::string front, std::string back, std::string
                top, std::string bottom, std::string left, std::string right);
        bool loadCubeMapSide(GLuint texture, GLenum side_target, const char*
                file_name);
        void draw();
        

    private:
        int indicesCount;
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        //GLfloat vertices[];
        //GLuint indices[];
        GLuint vaoId;
        GLuint vertexBufferId;
        GLuint indexBufferId;
        GLuint texture;

};

#endif /* ifndef INCLUDED_SKYBOX */
