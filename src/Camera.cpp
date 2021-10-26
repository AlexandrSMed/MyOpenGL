#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

glm::mat4 TDW::Camera::viewMatrix() const {
    return glm::lookAt(cameraPosition, cameraLookAt, cameraUpDirection);
}

glm::mat4 TDW::Camera::projectionMatrix() const {
    // TODO: optimize it
    GLint data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    return glm::perspective(glm::radians(45.0f), float(data[2]) / float(data[3]), 2.0f, 100.0f);
}
