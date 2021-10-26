#pragma once
struct GLFWwindow;

namespace TDW {
    class Camera;
    class EventListener {
    public:
        virtual void mouseDidMove(GLFWwindow* window, const Camera& camera, double xPos, double yPos) = 0;
        virtual void contextDidLoad(GLFWwindow* window, const Camera& camera, int width, int height) = 0;
        virtual void windowDidResize(GLFWwindow* window, const Camera& camera, int width, int height) = 0;
        virtual void keyDidSendAction(GLFWwindow* window, const Camera& camera, int key, int action) = 0;
        
        virtual ~EventListener() = default;
    };
}
