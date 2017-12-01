#ifndef INCLUDED_PLANE
#define INCLUDED_PLANE

#include <iostream>
#include <GL/glew.h>

struct Vertex {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
};

class Plane {
    
    public:
        
        //Plane();
        Plane(int width=20, int height=20);
        ~Plane();

        void Draw();


    private:

        int width;
        int height;
        int indicesCount;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint vaoId;
        GLuint bufferId;
        GLuint indexBufferId;

};

#endif /* ifndef INCLUDED_PLANE */
