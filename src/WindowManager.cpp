#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include "WindowManager.h"

#pragma region Private

void TDW::WindowManager::windowDidResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    for (auto renderer : renderers) {
        renderer->windowDidResize(window, width, height);
    }
}

void TDW::WindowManager::mouseDidMove(GLFWwindow* window, double xPos, double yPos) {
    for (auto renderer : renderers) {
        renderer->mouseDidMove(window, xPos, yPos);
    }
}

void TDW::WindowManager::keyDidSendAction(GLFWwindow* window, int key, int action) {
    for (auto renderer : renderers) {
        renderer->keyDidSendAction(window, key, action);
    }
}

#pragma endregion

TDW::WindowManager& TDW::WindowManager::shared() {
    static WindowManager* manager = new WindowManager();
    return *manager;
}

bool TDW::WindowManager::configureOpenGL(int major, int minor) {

    if (glfwInit() == GLFW_FALSE) {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

GLFWwindow* TDW::WindowManager::presentWindow(int width, int height, std::string title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        terminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* mWindow, int nWidth, int nHeight) {
        TDW::WindowManager::shared().windowDidResize(mWindow, nWidth, nHeight);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* mWindow, double xPos, double yPos) {
        TDW::WindowManager::shared().mouseDidMove(mWindow, xPos, yPos);
    });
    glfwSetKeyCallback(window, [](GLFWwindow* mWindow, int key, int, int action, int) {
        TDW::WindowManager::shared().keyDidSendAction(mWindow, key, action);
    });
    for (auto renderer : renderers) {
        renderer->contextDidLoad(window, width, height);
    }
    return window;
}

bool TDW::WindowManager::initGLAD() {
    auto loadProc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    return gladLoadGLLoader(loadProc);
}

void TDW::WindowManager::runWindowLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
            break;
        }
        for (auto& renderer : renderers) {
            renderer->draw(window);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void TDW::WindowManager::terminate() {
    glfwTerminate();
}

void TDW::WindowManager::addRenderer(Renderer* renderer) {
    renderers.push_back(renderer);
    auto window = glfwGetCurrentContext();
    if (window) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        renderer->contextDidLoad(window, width, height);
    }
}

TDW::WindowManager::~WindowManager() {
    glfwTerminate();
}
