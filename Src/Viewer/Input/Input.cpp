#include <iostream>
#include "Input.h"

void Input::Init(Window window) {
    GLFWwindow* rawWindow = window.GetWindow();

    Input::Flush();
    Input::ToggleCursor(window);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(rawWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetKeyCallback(rawWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;

        if (key == GLFW_KEY_ESCAPE)
            exit(EXIT_SUCCESS);
    });

    glfwSetCursorPosCallback(rawWindow, [](GLFWwindow* window, double xPos, double yPos) {
        if (firstFrame) {
            cursorX = xPos;
            cursorY = yPos;
            firstFrame = false;
        }

        float xOffset = xPos - cursorX;
        float yOffset = cursorY - yPos;

        cursorX = xPos;
        cursorY = yPos;

        float sensitivity = 0.05f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    });
}

void Input::Update() {

}

bool Input::GetKeyDown(int keycode) {
    if (keycode < 0 || keycode >= 1024) return false;
    return keys[keycode];
}

std::pair<float, float> Input::GetMouseYawAndPitch() {
    return std::pair<float, float>(yaw, pitch);
}

void Input::Flush() {
    for (bool & key : keys) {
        key = false;
    }
}

float Input::pitch = 0;
float Input::yaw = -90;
float Input::cursorX = 0;
float Input::cursorY = 0;
bool Input::keys[1024] = {};
bool Input::firstFrame = true;
bool Input::isCursor = true;

void Input::ToggleCursor(Window window) {
    isCursor = !isCursor;
    if (isCursor) {
        glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
