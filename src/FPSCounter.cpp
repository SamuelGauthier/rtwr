/**
 * @file FPSCounter.cpp
 * @brief Timer class used to track the rendering time of one frame.
 * @author Samuel Gauthier
 */
#include <iostream>
#include <GLFW/glfw3.h>
#include "FPSCounter.h"

/**
 * @brief Default constructor
 */
FPSCounter::FPSCounter() {

    this->lastTime = glfwGetTime();
    this->currentTime = lastTime;
    this->nbrFrames = 0;
}

/**
 * @brief Default destructor
 */
FPSCounter::~FPSCounter() {}

/**
 * @brief Update the timer and prints the time used to render the frame.
 */
void FPSCounter::update() {

    this->currentTime = glfwGetTime();
    nbrFrames++;

    if (currentTime - this->lastTime >= 1.0) {
        printf("%f ms/frame\n", 1000.0/double(nbrFrames));
        nbrFrames = 0;
        this->lastTime += 1.0;
    }
}

/**
 * @brief Get the current time
 *
 * @return The current time
 */
double FPSCounter::getCurrentTime() {
    return this->currentTime;
}
