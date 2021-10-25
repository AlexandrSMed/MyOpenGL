#include <iostream>
#include "glad/glad.h"
#include "WindowManager.h"
#include "renderers/BasicRenderer.h"
#include "renderers/StaticRenderer.h"

int main() {
    auto &windowManager = TDW::WindowManager::shared();
    if (!windowManager.configureOpenGL(3, 3)) {
        return -1;
    }

    auto window = windowManager.presentWindow(1024, 768, "MyOpenGL");
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
    windowManager.addRenderer(new TDW::StaticRenderer(2048, 10));
    windowManager.runWindowLoop(window);
    windowManager.terminate();
}
