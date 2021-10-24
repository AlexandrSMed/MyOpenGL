#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

namespace TDW {
	class BasicRenderer : public Renderer {
	public:
		BasicRenderer() : modelMatrix(1), viewMatrix(1), projectionMatrix(1) {
			modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0, 1, 1));
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -4.0f));
		}

		void draw(GLFWwindow* window) override;
		void contextDidLoad(GLFWwindow* window, int width, int height) override;
		void handleInput(GLFWwindow* window) override;
		void windowDidResize(GLFWwindow* window, int width, int height) override;
		~BasicRenderer() override;
	private:
		GLuint vertexAO;
		GLuint shaderProgram;

		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		
		void slowboatTranformations();
		double timePassed();
		void refreshProjectionMatrix();
		void setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
		void attachTexture(std::string texturePath);
		void applyTransformMatrix(std::string name, const glm::mat4& matrix);
	};
}

