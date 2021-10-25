#pragma once
#include <vector>
#include <glm/fwd.hpp>
#include "Renderer.h"

namespace TDW {
    class StaticRenderer : public Renderer {
    public:
        StaticRenderer(size_t count, unsigned radius);

        void draw(GLFWwindow* window, Camera& camera) override;
        void contextDidLoad(GLFWwindow* window, Camera& camera, int width, int height) override;
        void mouseDidMove(GLFWwindow* window, Camera& camera, double xPos, double yPos) override;
        void windowDidResize(GLFWwindow* window, Camera& camera, int width, int height) override;
        void keyDidSendAction(GLFWwindow* window, Camera& camera, int key, int action) override;
        ~StaticRenderer() override;

    private:
        GLuint vertexAO;
        GLuint shaderProgram;
        std::vector<std::pair<glm::mat4, float>> modelMatrices;
    };
}

