#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 worldUp);
    ~Camera();

    void LookAt();
    void Update();
    glm::mat4 GetViewMatrix();

    glm::vec3 GetPosition();
    glm::vec3 GetFront();

private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed = 15.0f;
    float sensitivity = 0.75f;

    void UpdateVectors();
};
