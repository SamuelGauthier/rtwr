//#define _USE_MATH_DEFINES // for C++  
#include <cmath>
#include <iostream>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

Camera::Camera(float theta, float phi, float radius, glm::vec3 target) :
    theta{theta}, phi{phi}, radius{radius}, target{target},
    projection{glm::mat4(1.0)}, view{glm::mat4(1.0)}, viewNeedsUpdate{true} {}

Camera::Camera(float x, float y, float z) {

    glm::vec3 spherical = toSpherical(x, y, z);
    Camera(spherical.x, spherical.y, spherical.z, glm::vec3(0.0, 0.0, 0.0));
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
    this->radius = (updatedDistance >= 0.0) ? updatedDistance : 0.0;
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

    this->view = glm::lookAt(toCartesian(), this->target, glm::vec3(0, 1, 0));
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
