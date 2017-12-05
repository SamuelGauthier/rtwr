#include <iostream>
#include <GLFW/glfw3.h>
#include "FPSCounter.h"

FPSCounter::FPSCounter() {

    this->lastTime = glfwGetTime();
    this->currentTime = lastTime;
    this->nbrFrames = 0;
}

FPSCounter::~FPSCounter() {}

void FPSCounter::update() {

    this->currentTime = glfwGetTime();
    nbrFrames++;

    if (currentTime - this->lastTime >= 1.0) {
        printf("%f ms/frame\n", 1000.0/double(nbrFrames));
        nbrFrames = 0;
        this->lastTime += 1.0;
    }
}

double FPSCounter::getCurrentTime() {
    return this->currentTime;
}
