#pragma once
#include <vector>
#include <string>
#include <glm/fwd.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"

namespace TDW {
    class Renderer {
    public:
        // TODO: make camera constant, and handle camera movement somewhere else
        virtual void mouseDidMove(GLFWwindow* window, Camera& camera, double xPos, double yPos) = 0;
        virtual void contextDidLoad(GLFWwindow* window, Camera& camera, int width, int height) = 0;
        virtual void windowDidResize(GLFWwindow* window, Camera& camera, int width, int height) = 0;
        virtual void draw(GLFWwindow* window, Camera& camera) = 0;
        virtual void keyDidSendAction(GLFWwindow* window, Camera& camera, int key, int action) = 0;

        virtual ~Renderer() = default;
    protected:
        GLuint loadShader(GLenum type, const char* source);
        GLuint linkProgram(const std::vector<GLuint>& shaders, bool deleteShaders = true);
        void enableVertexAttribute(GLuint program, std::string name, size_t size, size_t stride = 0, int offset = 0);
        void disableVertexAttribute(GLuint program, std::string name);
        void attachMatrix(GLuint program, std::string name, const glm::mat4& matrix);
        GLuint setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
    };
}
