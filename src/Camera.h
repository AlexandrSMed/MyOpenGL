#pragma once
#include <glm/glm.hpp>
namespace TDW {
    class Camera {
    public:
        const static int undefinedSize;

        glm::vec3 cameraPosition;
        glm::vec3 cameraUpDirection;
        glm::vec3 cameraLookAt;

        void refreshProjectionMatrix(float angle = 45.0f, float near = 2.0f, float far = 100.0f, int width = undefinedSize, int height = undefinedSize);
        glm::mat4 getProjectionMatrix() const;
        glm::mat4 makeViewMatrix() const;
    private:
        glm::mat4 projectionMatrix;
    };
}
