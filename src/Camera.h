/**
 * @file Camera.h
 * @brief Camera class in spherical coordinates.
 * @author Samuel Gauthier
 */
#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include <glm/glm.hpp>

class Camera {

    public:

        /**
         * @brief Default Constructor.
         *
         * @param position The camera position
         * @param target The look at target
         * @param up The up vector
         * @param projection The projection matrix
         */
        Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, glm::mat4
                projection);
        /**
         * @brief Default Destructor
         */
        ~Camera();
        /**
         * @brief Rotates the camera with the angle given in arguments.
         *
         * @param dTheta Theta angle in radians
         * @param dPhi Phi angle in radians
         */
        void rotate(float dTheta, float dPhi);
        /**
         * @brief Zoom the camera in or out given the distance in arguments.
         *
         * @param distance The distance to zoom
         */
        void zoom(float distance);
        /**
         * @brief Pan the camera with the amount given in arguments
         *
         * @param dx The amount in the x direction
         * @param dy The amount in the y direction
         */
        void pan(float dx, float dy);
        
        /**
         * @brief Returns the projection matrix of the camera.
         *
         * @return The projection matrix of the camera
         */
        glm::mat4 getProjectionMatrix();
        /**
         * @brief Returns the view matrix of the camera.
         *
         * @return The view matrix
         */
        glm::mat4 getViewMatrix();
        /**
         * @brief Returns the cartesian coordinates of the camera.
         *
         * @return The cartesian coordinates of the camera.
         */
        glm::vec3 toCartesian();
        /**
         * @brief Returns the spherical coordinates given cartesian ones and
         * their relative center.
         *
         * @param x The x cartesian coordinate
         * @param y The y cartesian coordinate
         * @param z The z cartesian coordinate
         * @param center Their relative center
         *
         * @return The corresponding spherical coordinates
         */
        static glm::vec3 toSpherical(float x, float y, float z, glm::vec3
                center);
        /**
         * @brief Returns the spherical coordinates given cartesian ones and
         * their relative center.
         *
         * @param cartesian The cartesian coordinates as a vector
         * @param center Their relative center
         *
         * @return The corresponding spherical coordinates
         */
        static glm::vec3 toSpherical(glm::vec3 cartesian, glm::vec3 center);

        

    private:
        float theta;
        float phi;
        float radius;
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 up;
        glm::mat4 projection;
        glm::mat4 view;
        bool viewNeedsUpdate;

        void updateViewMatrix();

};

#endif /* ifndef INCLUDED_CAMERA */
