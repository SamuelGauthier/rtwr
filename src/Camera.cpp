/**
 * @file Camera.cpp
 * @brief Camera class in spherical coordinates.
 * @author Samuel Gauthier
 */
#include <cmath>
#include <iostream>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

/**
 * @brief Default Constructor. Creates a camera with a position, looking at a
 * target position with a given up vector and projection matrix.
 *
 * @param position The camera position
 * @param target The look at target
 * @param up The up vector
 * @param projection The projection matrix
 */
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up,
        glm::mat4 projection) {

    this->position = position;
    this->target = target;

    glm::vec3 spherical = Camera::toSpherical(position, target);

    this->theta = spherical.x;
    this->phi = spherical.y;
    this->radius = spherical.z;
    this->up = up;
    this->projection = projection;
    this->view = glm::lookAt(position, target, up);
    this->viewNeedsUpdate = true;
}

/**
 * @brief Default Destructor
 */
Camera::~Camera() {}

/**
 * @brief Rotates the camera with the angle given in arguments.
 *
 * @param dTheta Theta angle in radians
 * @param dPhi Phi angle in radians
 */
void Camera::rotate(float dTheta, float dPhi) {

    this->viewNeedsUpdate = true;

    float updatedTheta = this->theta - dTheta;
    float updatedPhi = this->phi - dPhi;

    if(updatedTheta < 0.0 && updatedTheta > 2*M_PI)
        updatedTheta = fmod(updatedTheta, 2*M_PI);

    this->theta = updatedTheta;

    if(updatedPhi >= 0.0 && updatedPhi <= M_PI)
        this->phi = updatedPhi;
}

/**
 * @brief Zoom the camera in or out given the distance in arguments.
 *
 * @param distance The distance to zoom
 */
void Camera::zoom(float distance) {

    this->viewNeedsUpdate = true;

    float updatedDistance = this->radius - distance;

    this->radius = (updatedDistance >= 0.0) ? updatedDistance : 0.1;
}

/**
 * @brief Pan the camera with the amount given in arguments
 *
 * @param dx The amount in the x direction
 * @param dy The amount in the y direction
 */
void Camera::pan(float dx, float dy) {

    this->viewNeedsUpdate = true;

    glm::vec3 OP = glm::normalize(this->target - toCartesian());
    glm::vec3 ex = glm::normalize(glm::cross(OP, this->up));
    glm::vec3 ey = glm::normalize(glm::cross(OP, ex));

    this->target += dx * ex + dy * ey;
}

/**
 * @brief Returns the projection matrix of the camera.
 *
 * @return The projection matrix of the camera
 */
glm::mat4 Camera::getProjectionMatrix() {

    return this->projection;
}

/**
 * @brief Returns the view matrix of the camera.
 *
 * @return The view matrix
 */
glm::mat4 Camera::getViewMatrix() {

    if(this->viewNeedsUpdate) {
        updateViewMatrix();
        this->viewNeedsUpdate = false;
    }

    return this->view;
}

/**
 * @brief Returns the cartesian coordinates of the camera.
 *
 * @return The cartesian coordinates of the camera.
 */
glm::vec3 Camera::toCartesian() {

    // OpenGL z coordinate points out of the screen.
    float x = this->target.x + this->radius * sin(this->phi) *
        sin(this->theta);
    float y = this->target.y + this->radius * cos(this->phi);
    float z = this->target.z + this->radius * sin(this->phi) *
        cos(this->theta);
    return glm::vec3(x, y, z);
}

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
glm::vec3 Camera::toSpherical(float x, float y, float z, glm::vec3 center) {

    float nx = x - center.x;
    float ny = y - center.y;
    float nz = z - center.z;

    float theta = atan(nx / nz);
    float phi = atan(sqrt(nx * nx + nz * nz) / ny);
    float radius = sqrt(nx * nx + ny * ny + nz * nz);

    return glm::vec3(theta, phi, radius);
}

/**
 * @brief Returns the spherical coordinates given cartesian ones and
 * their relative center.
 *
 * @param cartesian The cartesian coordinates as a vector
 * @param center Their relative center
 *
 * @return The corresponding spherical coordinates
 */
glm::vec3 Camera::toSpherical(glm::vec3 cartesian, glm::vec3 center) {
    
    return Camera::toSpherical(cartesian.x, cartesian.y, cartesian.z, center);
}

void Camera::updateViewMatrix() {

    this->view = glm::lookAt(toCartesian(), this->target, this->up);
}
