/**
 * @file Plane.h
 * @brief Plane definition
 * @author Samuel Gauthier
 */
#ifndef INCLUDED_PLANE
#define INCLUDED_PLANE

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

/**
 * @brief Vertex with xyzw model coordinates, rgba values and xyzw normal
 * coordinates
 */
struct Vertex {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
    GLfloat Normal[4];
};

/**
 * @brief Represents a Plane with no possible rotation.
 */
class Plane {
    
    public:
        
        /**
         * @brief Default Plane constructor.
         *
         * @param width The width of the plane.
         * @param height The height of the plane.
         * @param center The center position of the plane.
         * @param resolution The resolution in vertex.
         */
        Plane(int width=2, int height=2, glm::vec3 center=glm::vec3(0, 0, 0),
                glm::vec2 resolution=glm::vec2(20, 20));
        /**
         * @brief Default Destructor
         */
        ~Plane();

        /**
         * @brief Generates OpenGL vertex array and buffers. Has to be called
         * befor the draw() method.
         */
        void setup();
        /**
         * @brief Draw the plane on the screen.
         */
        void draw();


    private:

        int width;
        int height;
        glm::vec3 center;
        glm::vec2 resolution;
        int indicesCount;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint vaoId;
        GLuint vertexBufferId;
        GLuint indexBufferId;

};

#endif /* ifndef INCLUDED_PLANE */
