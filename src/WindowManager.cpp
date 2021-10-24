#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include "WindowManager.h"

namespace TDW {
#pragma region Private

    void WindowManager::windowDidResize(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        for (auto renderer : renderers) {
            renderer->windowDidResize(window, width, height);
        }
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
            terminate();
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* mWindow, int nWidth, int nHeight) {
            WindowManager::shared().windowDidResize(mWindow, nWidth, nHeight);
        });

        for (auto renderer : renderers) {
            renderer->contextDidLoad(window, width, height);
        }
        return window;
    }

    bool WindowManager::initGLAD() {
        auto loadProc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
        return gladLoadGLLoader(loadProc);
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
        auto window = glfwGetCurrentContext();
        if (window) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            renderer->contextDidLoad(window, width, height);
        }
    }

    WindowManager::~WindowManager() {
        glfwTerminate();
    }
}
