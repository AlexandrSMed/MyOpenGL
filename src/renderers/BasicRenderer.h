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
            }) : textureStack(aTextureStack), activeTextureIndex(0), textureSwitchDeltaTime(0), textureSwitching(false),
            textureTransitionAlpha(0), lastXMousePos(0), lastYMousePos(0), vertexAO(0), shaderProgram(0), modelMatrix(1),
            projectionMatrix(1) {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.8, 0));
        }

        void draw(GLFWwindow* window, const Camera& camera) override;
        void contextDidLoad(GLFWwindow* window, const Camera& camera, int width, int height) override;
        void mouseDidMove(GLFWwindow* window, const Camera& camera, double xPos, double yPos) override;
        void windowDidResize(GLFWwindow* window, const Camera& camera, int width, int height) override;
        void keyDidSendAction(GLFWwindow* window, const Camera& camera, int key, int action) override;
        ~BasicRenderer() override;
    private:
        std::vector<std::string> textureStack;
        GLint activeTextureIndex;
        double textureSwitchDeltaTime;
        bool textureSwitching;
        float textureTransitionAlpha;

        double lastXMousePos;
        double lastYMousePos;

        GLuint vertexAO;
        GLuint shaderProgram;

        glm::mat4 modelMatrix;
        glm::mat4 projectionMatrix;
        
        void switchTexture();
        void slowboatTranformations();
        void attachTexture(std::string texturePath, int glTextureIndex);
    };
}

