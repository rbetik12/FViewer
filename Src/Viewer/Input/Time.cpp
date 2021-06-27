#include <GLFW/glfw3.h>
#include "Time.h"

void Time::Update() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float Time::lastFrame = 0.0f;
float Time::deltaTime;
float Time::currentFrame;
