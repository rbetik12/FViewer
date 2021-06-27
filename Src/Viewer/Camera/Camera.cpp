#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"
#include "../Input/Input.h"
#include "../Input/Time.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp) : position(position), worldUp(worldUp), yaw(-90.0f), pitch(0.0f) {
    UpdateVectors();
}

Camera::~Camera() {

}

void Camera::LookAt() {

}

void Camera::Update() {
    float cameraSpeed = movementSpeed * Time::deltaTime;
    if (Input::GetKeyDown(GLFW_KEY_W))
        position += cameraSpeed * front;
    if (Input::GetKeyDown(GLFW_KEY_S))
        position -= cameraSpeed * front;
    if (Input::GetKeyDown(GLFW_KEY_A))
        position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (Input::GetKeyDown(GLFW_KEY_D))
        position += glm::normalize(glm::cross(front, up)) * cameraSpeed;


    auto pos = Input::GetMouseYawAndPitch();
    yaw = pos.first;
    pitch = pos.second;

    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 rotatedFront;
    rotatedFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    rotatedFront.y = sin(glm::radians(pitch));
    rotatedFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(rotatedFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetPosition() {
    return position;
}

glm::vec3 Camera::GetFront() {
    return front;
}