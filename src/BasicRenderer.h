#pragma once
#include "Renderer.h"

namespace TDW {
	class BasicRenderer : public Renderer {
	public:
		void draw(GLFWwindow* window) override;
		void handleInput(GLFWwindow* window) override;
	};
}

