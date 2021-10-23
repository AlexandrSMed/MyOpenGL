#pragma once
#include <vector>
#include "Renderer.h"

namespace TDW {
	class BasicRenderer : public Renderer {
	public:
		void draw(GLFWwindow* window) override;
		void contextDidLoad(GLFWwindow* window) override;
		void handleInput(GLFWwindow* window) override;
		~BasicRenderer() override;
	private:
		GLuint vertexAO;
		GLuint vertexBO;
		GLuint shaderProgram;

		void setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
	};
}

