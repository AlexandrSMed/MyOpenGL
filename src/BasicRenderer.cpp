#include "BasicRenderer.h"

namespace TDW {
	void BasicRenderer::draw(GLFWwindow*) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void BasicRenderer::handleInput(GLFWwindow*) {
	}
}
