#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "Camera.h"

namespace TDW {
    class BasicRenderer : public Renderer {
    public:
        BasicRenderer(std::vector<std::string> aTextureStack = {
            "assets/texture_austmar.jpg", "assets/texture_gantas.jpg", "assets/texture_harrison.jpg"
            }) : textureStack(aTextureStack), modelMatrix(1), projectionMatrix(1) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.8, 0));
        }

        void draw(GLFWwindow* window, Camera& camera) override;
        void contextDidLoad(GLFWwindow* window, Camera& camera, int width, int height) override;
        void mouseDidMove(GLFWwindow* window, Camera& camera, double xPos, double yPos) override;
        void windowDidResize(GLFWwindow* window, Camera& camera, int width, int height) override;
        void keyDidSendAction(GLFWwindow* window, Camera& camera, int key, int action) override;
        ~BasicRenderer() override;
    private:
        std::vector<std::string> textureStack;
        unsigned activeTextureIndex = 0;
        double textureSwitchDeltaTime;
        bool textureSwitching = false;
        float textureTransitionAlpha = 0;

        double lastFrameTime = 0;
        double deltaTime = 0;
        double lastXMousePos;
        double lastYMousePos;

        GLuint vertexAO;
        GLuint shaderProgram;

        glm::mat4 modelMatrix;
        glm::mat4 projectionMatrix;
        
        void switchTexture();
        void slowboatTranformations();
        void refreshDeltaTime();
        void attachTexture(std::string texturePath, int glTextureIndex);
    };
}

