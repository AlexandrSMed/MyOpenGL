#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "Camera.h"

namespace TDW {
	class BasicRenderer : public Renderer {
	public:
		BasicRenderer() : modelMatrix(1), projectionMatrix(1) {
			camera.cameraUpDirection = glm::vec3(0, 1, 0);
			camera.cameraLookAt = glm::vec3(0);
			camera.cameraPosition = glm::vec3(4);
		}

		void draw(GLFWwindow* window) override;
		void contextDidLoad(GLFWwindow* window, int width, int height) override;
		void mouseDidMove(GLFWwindow* window, double xPos, double yPos) override;
		void windowDidResize(GLFWwindow* window, int width, int height) override;
		~BasicRenderer() override;
	private:
		double lastFrameTime = 0;
		double deltaTime = 0;
		double lastXMousePos;
		double lastYMousePos;

		GLuint vertexAO;
		GLuint shaderProgram;

		glm::mat4 modelMatrix;
		glm::mat4 projectionMatrix;
		Camera camera;
		
		void slowboatTranformations();
		void refreshDeltaTime();
		void refreshProjectionMatrix();
		void setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
		void attachTexture(std::string texturePath);
		void applyTransformMatrix(std::string name, const glm::mat4& matrix);
	};
}

