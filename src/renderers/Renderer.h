#pragma once
#include <vector>
#include <string>
#include <glm/fwd.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "EventListener.h"

namespace TDW {
    class Renderer : public EventListener {
    public:
        virtual void draw(GLFWwindow* window, const Camera& camera) = 0;

        virtual ~Renderer() override = default;
    protected:
        GLuint loadShader(GLenum type, const char* source);
        GLuint linkProgram(const std::vector<GLuint>& shaders, bool deleteShaders = true);
        void enableVertexAttribute(GLuint program, std::string name, size_t size, size_t stride = 0, int offset = 0);
        void disableVertexAttribute(GLuint program, std::string name);
        void attachMatrix(GLuint program, std::string name, const glm::mat4& matrix);
        GLuint setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices);
    };
}
