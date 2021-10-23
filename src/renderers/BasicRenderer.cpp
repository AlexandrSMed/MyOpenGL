#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
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
			// Vertices				// Texture	
			0.5f,	0.5f,	0.0f,	1.0f,	1.0f,
			0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
			-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,
			-0.5f,	0.5f,	0.0f,	0.0f,	1.0f
		}, {
			2,	3,	0,
			2,	0,	1
		});
		auto stride = sizeof(float) * 5;
		enableVertexAttribute(shaderProgram, "aPos", 3, stride, 0);
		enableVertexAttribute(shaderProgram, "aTextCoord", 2, stride, sizeof(float) * 3);
		attachTexture("assets/texture_austmar.jpg");
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




}
