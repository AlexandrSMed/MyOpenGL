#include <iostream>
#include "glad/glad.h"
#include "WindowManager.h"
#include "renderers/BasicRenderer.h"

int main() {
	std::cout << "Hello, world!" << std::endl;
    auto &windowManager = TDW::WindowManager::shared();
    if (!windowManager.configureOpenGL(3, 3)) {
        return -1;
    }

    auto window = windowManager.presentWindow(800, 600, "MyOpenGL");
    if (!window) {
        return -1;
    }
    if (!windowManager.initGLAD()) {
        return -1;
    }
#ifdef LOG
    std::cout << "GLAD has been initialized with the OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#endif // LOG
    windowManager.addRenderer(new TDW::BasicRenderer());
    windowManager.runWindowLoop(window);
    windowManager.terminate();
}
