#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

const int TDW::Camera::undefinedSize = -1;

glm::mat4 TDW::Camera::makeViewMatrix() const {
    return glm::lookAt(cameraPosition, cameraLookAt, cameraUpDirection);
}

void TDW::Camera::refreshProjectionMatrix(float angle, float near, float far, int width, int height) {
    if (width == undefinedSize || height == undefinedSize) {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);
        width = data[2];
        height = data[3];
    }
    projectionMatrix = glm::perspective(glm::radians(angle), float(width) / float(height), near, far);
}

glm::mat4 TDW::Camera::getProjectionMatrix() const {
    return projectionMatrix;
}


