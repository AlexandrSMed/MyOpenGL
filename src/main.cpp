#include <iostream>
#include "glad/glad.h"
#include "WindowManager.h"
#include "BasicRenderer.h"

int main() {
	std::cout << "Hello, world!" << std::endl;
    auto &windowManager = TDW::WindowManager::shared();
    if (!windowManager.configureOpenGL(3, 2)) {
        return -1;
    }

    auto window = windowManager.presentWindow(800, 600, "MyOpenGL");
    if (!window) {
        return -1;
    }
    if (!windowManager.initGLAD()) {
        return -1;
    }
    windowManager.addRenderer(new TDW::BasicRenderer());
    windowManager.runWindowLoop(window);
    windowManager.terminate();
}
