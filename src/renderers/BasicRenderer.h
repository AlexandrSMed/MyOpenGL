#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

namespace TDW {
	class BasicRenderer : public Renderer {
	public:
		BasicRenderer() : modelMatrix(1) {
			modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0, 1, 1));
		}

		void draw(GLFWwindow* window) override;
		void contextDidLoad(GLFWwindow* window) override;
		void handleInput(GLFWwindow* window) override;
		~BasicRenderer() override;
	private:
		GLuint vertexAO;
		GLuint shaderProgram;

		glm::mat4 modelMatrix;
		
		void slowboatTranformations();
		double timePassed();
		void setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
		void attachTexture(std::string texturePath);
		void applyTransformMatrix(std::string name, const glm::mat4& matrix);
	};
}

