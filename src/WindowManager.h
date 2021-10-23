#pragma once
#include <string>
#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include "renderers/Renderer.h"

namespace TDW {

	class WindowManager {

	public:
		static WindowManager& shared();
		bool configureOpenGL(int major, int minor);
		GLFWwindow* presentWindow(int width, int height, std::string title);
		bool initGLAD();
		void runWindowLoop(GLFWwindow* window);
		void terminate();
		void addRenderer(Renderer* renderer);

		~WindowManager();
	private:
		std::vector<Renderer*> renderers;
	};
}
