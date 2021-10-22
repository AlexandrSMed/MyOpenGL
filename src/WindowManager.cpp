#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"

namespace TDW {
#pragma region Private

    void windowDidResize(GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    }

#pragma endregion

    WindowManager& WindowManager::shared() {
        static WindowManager* manager = new WindowManager();
        return *manager;
    }

    bool WindowManager::configureOpenGL(int major, int minor) {

        if (glfwInit() == GLFW_FALSE) {
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return true;
    }

    GLFWwindow* WindowManager::presentWindow(int width, int height, std::string title) {
        GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            return nullptr;
        }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, windowDidResize);
        return window;
    }

    bool WindowManager::initGLAD() {
        return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }

    void WindowManager::runWindowLoop(GLFWwindow* window) {
        while (!glfwWindowShouldClose(window)) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
                break;
            }
            for (auto& renderer : renderers) {
                renderer->handleInput(window);
                renderer->draw(window);
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void WindowManager::terminate() {
        glfwTerminate();
    }

    void WindowManager::addRenderer(Renderer* renderer) {
        renderers.push_back(renderer);
    }

    WindowManager::~WindowManager() {
        glfwTerminate();
    }
}
