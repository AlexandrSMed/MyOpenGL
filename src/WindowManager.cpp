#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"
#include "WindowManager.h"

#pragma region Private

void TDW::WindowManager::windowDidResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    camera.refreshProjectionMatrix();
    for (auto renderer : renderers) {
        renderer->windowDidResize(window, camera, width, height);
    }
}

void TDW::WindowManager::mouseDidMove(GLFWwindow* window, double xPos, double yPos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        static const auto cameraSpeed = Utils::deltaTime() * 0.8;

        float xDelta = static_cast<float>((xPos - lastXMousePos) * cameraSpeed);

        auto yRotationMatrix = glm::rotate(glm::mat4(1), -xDelta, glm::vec3(0, 1, 0));
        auto rotationResult = yRotationMatrix * glm::vec4(camera.cameraPosition, 1);
        camera.cameraPosition = glm::vec3(rotationResult);
    }
    lastXMousePos = xPos;
    for (auto renderer : renderers) {
        renderer->mouseDidMove(window, camera, xPos, yPos);
    }
}

void TDW::WindowManager::keyDidSendAction(GLFWwindow* window, int key, int action) {
    for (auto renderer : renderers) {
        renderer->keyDidSendAction(window, camera, key, action);
    }
}

#pragma endregion

TDW::WindowManager::WindowManager() {
    camera.cameraUpDirection = glm::vec3(0, 1, 0);
    camera.cameraLookAt = glm::vec3(0);
    camera.cameraPosition = glm::vec3(4);
}

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
    camera.refreshProjectionMatrix(45, 2, 100, width, height);
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
        renderer->contextDidLoad(window, camera, width, height);
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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto& renderer : renderers) {
            renderer->draw(window, camera);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        Utils::deltaTime(true);
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
        renderer->contextDidLoad(window, camera, width, height);
    }
}

TDW::WindowManager::~WindowManager() {
    glfwTerminate();
}
