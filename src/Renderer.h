#pragma once
#include <GLFW/glfw3.h>

namespace TDW {
	class Renderer {
	public:
		virtual void handleInput(GLFWwindow* window) = 0;
		virtual void draw(GLFWwindow* window) = 0;
		virtual ~Renderer() = default;
	};
}
