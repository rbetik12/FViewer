#include "Light.h"

void Light::SetDirection(glm::vec3& direction) {
    this->direction = direction;
}

void Light::SetAmbientColor(glm::vec3& color) {
    ambientColor = color;
}

void Light::SetDiffuseColor(glm::vec3& color) {
    diffuseColor = color;
}
