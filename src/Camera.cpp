#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

glm::mat4 TDW::Camera::viewMatrix() {
    return glm::lookAt(cameraPosition, cameraLookAt, cameraUpDirection);
}
