#pragma once

#include <glm/vec3.hpp>

class Light {
public:
    inline glm::vec3& GetDirection() { return direction; }
    inline glm::vec3& GetAmbientColor() { return ambientColor; }
    inline glm::vec3& GetDiffuseColor() { return diffuseColor; }

    void SetDirection(glm::vec3& direction);
    void SetAmbientColor(glm::vec3& color);
    void SetDiffuseColor(glm::vec3& color);

    Light() : direction(3.0f, 5.0f, 0.0f), diffuseColor(1.0f), ambientColor(0.8f) {}
private:
    glm::vec3 direction;
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
};
