#include <iostream>
#include <glad/glad.h>
#include "BasicRenderer.h"
#include "BasicShaders.h"
#include "Utils.h"

namespace TDW {
	
	void TDW::BasicRenderer::contextDidLoad(GLFWwindow*) {
		std::vector<GLuint> shaders {
			loadShader(GL_VERTEX_SHADER, BasicShaders::vertex),
			loadShader(GL_FRAGMENT_SHADER, BasicShaders::fragment)
		};
		shaderProgram = linkProgram(shaders);
		glUseProgram(shaderProgram);

		setVertices({
			0.5f,	0.5f,	0.0f,
			0.5f,	-0.5f,	0.0f,
			-0.5f,	-0.5f,	0.0f,
			-0.5f,	0.5f,	0.0f 
		}, {
			2,	3,	0,
			2,	0,	1
		});
		enableVertexAttribute(shaderProgram, "aPos", 3);

	}

	void BasicRenderer::draw(GLFWwindow*) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	}

	void BasicRenderer::handleInput(GLFWwindow*) {

	}

	BasicRenderer::~BasicRenderer() {
		glDeleteProgram(shaderProgram);
	}

	void BasicRenderer::setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices) {
		glGenVertexArrays(1, &vertexAO); 
		glBindVertexArray(vertexAO);

		glGenBuffers(1, &vertexBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesData.size(), verticesData.data(), GL_STATIC_DRAW);

		GLuint elementsBO;
		glGenBuffers(1, &elementsBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}
}
