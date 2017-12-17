//#define _USE_MATH_DEFINES // for C++  
#include <cmath>
#include <iostream>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up,
        glm::mat4 projection) {

    glm::vec3 spherical = Camera::toSpherical(position);

    this->theta = spherical.x;
    this->phi = spherical.y;
    this->radius = spherical.z;
    this->position = position;
    this->target = target;
    this->up = up;
    this->projection = projection;
    this->view = glm::lookAt(position, target, up);
    this->viewNeedsUpdate = true;
}

Camera::~Camera() {}

void Camera::rotate(float dTheta, float dPhi) {

    this->viewNeedsUpdate = true;

    float updatedTheta = this->theta - dTheta;
    float updatedPhi = this->phi - dPhi;

    // TODO : Fix floating point comparison
    if(updatedTheta >= 0.0 && updatedTheta <= 2*M_PI)
        this->theta = updatedTheta;

    // TODO : Fix floating point comparison
    if(updatedPhi >= 0.0 && updatedPhi <= M_PI)
        this->phi = updatedPhi;
}

void Camera::zoom(float distance) {

    this->viewNeedsUpdate = true;

    float updatedDistance = this->radius - distance;

    // TODO : Fix floating point comparison
    this->radius = (updatedDistance >= 0.0) ? updatedDistance : 0.1;
}

// TODO: Implement or not?
void Camera::pan(float dx, float dy) {}

glm::mat4 Camera::getProjectionMatrix() {

    return this->projection;
}

glm::mat4 Camera::getViewMatrix() {

    if(this->viewNeedsUpdate) {
        updateViewMatrix();
        this->viewNeedsUpdate = false;
    }

    return this->view;
}

void Camera::updateViewMatrix() {

    this->view = glm::lookAt(toCartesian(), this->target, this->up);
}

glm::vec3 Camera::toCartesian() {

    // OpenGL z coordinate points out of the screen.
    float x = this->radius * sin(this->phi) * sin(this->theta);
    float y = this->radius * cos(this->phi);
    float z = this->radius * sin(this->phi) * cos(this->theta);
    return glm::vec3(x, y, z);
}

glm::vec3 Camera::toSpherical(float x, float y, float z) {

    float theta = atan(x / z);
    float phi = atan(sqrt(x * x + z * z) / y);
    float radius = sqrt(x * x + y * y + z * z);

    return glm::vec3(theta, phi, radius);
}


glm::vec3 Camera::toSpherical(glm::vec3 cartesian) {
    
    return Camera::toSpherical(cartesian.x, cartesian.y, cartesian.z);
}
