#pragma once
#include <glm/glm.hpp>
namespace TDW {
    struct Camera {
        glm::vec3 cameraPosition;
        glm::vec3 cameraUpDirection;
        glm::vec3 cameraLookAt;

        glm::mat4 viewMatrix();
    };
}
