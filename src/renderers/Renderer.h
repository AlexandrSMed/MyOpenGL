#pragma once
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

namespace TDW {
	class Renderer {
	public:
		virtual void handleInput(GLFWwindow* window) = 0;
		virtual void contextDidLoad(GLFWwindow* window) = 0;
		virtual void draw(GLFWwindow* window) = 0;

		virtual ~Renderer() = default;
	protected:
		GLuint loadShader(GLenum type, const char* source);
		GLuint linkProgram(const std::vector<GLuint>& shaders, bool deleteShaders = true);
		void enableVertexAttribute(GLuint program, std::string name, size_t size, size_t stride = 0, int offset = 0);
		void disableVertexAttribute(GLuint program, std::string name);
	};
}
