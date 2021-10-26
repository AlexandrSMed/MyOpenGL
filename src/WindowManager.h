#pragma once
#include <string>
#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include "renderers/Renderer.h"
#include "Camera.h"


namespace TDW {

    class WindowManager {

    public:
        WindowManager();
        static WindowManager& shared();
        bool configureOpenGL(int major, int minor);
        GLFWwindow* presentWindow(int width, int height, std::string title);
        bool initGLAD();
        void runWindowLoop(GLFWwindow* window);
        void terminate();
        void addRenderer(Renderer* renderer);

        ~WindowManager();
    private:
        Camera camera;
        double lastXMousePos;
        std::vector<Renderer*> renderers;

        void keyDidSendAction(GLFWwindow* window, int key, int action);
        void windowDidResize(GLFWwindow* window, int width, int height);
        void mouseDidMove(GLFWwindow* window, double xPos, double yPos);
    };
}
