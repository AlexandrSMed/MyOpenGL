#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include "BasicRenderer.h"
#include "BasicShaders.h"
#include "Utils.h"

namespace TDW {

#pragma region Private
	void BasicRenderer::slowboatTranformations() {
		auto timeFrame = timePassed();
		float angle = timeFrame * 32;
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 1, 1));
	}

	double BasicRenderer::timePassed() {
		static double time = glfwGetTime();
		auto difference = glfwGetTime() - time;
		time = glfwGetTime();
		return difference;
	}

	void BasicRenderer::setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices) {
		glGenVertexArrays(1, &vertexAO); 
		glBindVertexArray(vertexAO);

		GLuint vertexBO;
		glGenBuffers(1, &vertexBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesData.size(), verticesData.data(), GL_STATIC_DRAW);

		GLuint elementsBO;
		glGenBuffers(1, &elementsBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	void BasicRenderer::attachTexture(std::string texturePath) {
		int width, height;
		auto imageData = stbi_load(texturePath.c_str(), &width, &height, nullptr, 0);

		if (!imageData) {
#ifdef LOG
			std::cout << "Could not load texture from path: " << texturePath << std::endl;
#endif // LOG
			return;
		}
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imageData);
	}

	void BasicRenderer::applyTransformMatrix(std::string name, const glm::mat4& matrix) {
		GLuint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void BasicRenderer::refreshProjectionMatrix() {
		GLint data[4];
		glGetIntegerv(GL_VIEWPORT, data);
		projectionMatrix = glm::perspective(glm::radians(45.0f), float(data[2]) / float(data[3]), 0.1f, 100.0f);
	}

#pragma endregion Private
	
	void TDW::BasicRenderer::contextDidLoad(GLFWwindow* window, int width, int height) {
		glEnable(GL_DEPTH_TEST);
		refreshProjectionMatrix();

		std::vector<GLuint> shaders {
			loadShader(GL_VERTEX_SHADER, BasicShaders::vertex),
			loadShader(GL_FRAGMENT_SHADER, BasicShaders::fragment)
		};
		shaderProgram = linkProgram(shaders);
		glUseProgram(shaderProgram);

		setVertices({
			// Vertices				// Texture	
			-0.5f,	-0.5f,	0.5f,	0.0f,	0.0f, // 0
			0.5f,	-0.5f,	0.5f,	1.0f,	0.0f, // 1
			0.5f,	0.5f,	0.5f,	1.0f,	1.0f, // 2
			-0.5f,	0.5f,	0.5f,	0.0f,	1.0f, // 3

			0.5f,	0.5f,	-0.5f,	0.0f,	1.0f, // 4
			0.5f,	-0.5,	-0.5f,	0.0f,	0.0f, // 5

			-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f, // 6
			-0.5f,	0.5f,	-0.5f,	1.0f,	1.0f, // 7

			-0.5f,	0.5f,	0.5f,	1.0f,	0.0f, // 8
			-0.5f,	0.5f,	-0.5f,	0.0f,	0.0f, // 9

			-0.5f,	-0.5f,	0.5f,	1.0f,	1.0f, // 10
			-0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f  // 11
		}, {
			0,	1,	2,		0,	3,	2,
			1,	5,	4,		1,	2,	4,
			5,	6,	7,		5,	4,	7,
			2,	4,	9,		2,	8,	9,
			8,	9,	11,		8,	10,	11,
			1,	5,	10,		5,	11,	10
		});
		auto stride = sizeof(float) * 5;
		enableVertexAttribute(shaderProgram, "aPos", 3, stride, 0);
		enableVertexAttribute(shaderProgram, "aTextCoord", 2, stride, sizeof(float) * 3);
		attachTexture("assets/texture_austmar.jpg");
	}

	void BasicRenderer::draw(GLFWwindow*) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		slowboatTranformations();
		applyTransformMatrix("projectionMatrix", projectionMatrix);
		applyTransformMatrix("viewMatrix", viewMatrix);
		applyTransformMatrix("modelMatrix", modelMatrix);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	}

	void BasicRenderer::handleInput(GLFWwindow*) {

	}

	void BasicRenderer::windowDidResize(GLFWwindow* window, int width, int heigth) {
		refreshProjectionMatrix();
	} 

	BasicRenderer::~BasicRenderer() {
		glDeleteProgram(shaderProgram);
		glDeleteBuffers(1, &vertexAO);
	}

}
