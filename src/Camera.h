#pragma once
#include <glm/glm.hpp>
namespace TDW {
    class Camera {
    public:
        glm::vec3 cameraPosition;
        glm::vec3 cameraUpDirection;
        glm::vec3 cameraLookAt;

        glm::mat4 projectionMatrix() const;
        glm::mat4 viewMatrix() const;
    };
}
