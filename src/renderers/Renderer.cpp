#include <iostream>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Utils.h"
#include "Renderer.h"

GLuint TDW::Renderer::loadShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_TRUE) {
        return shader;
    } else {
#ifdef LOG
        char compileMessage[512];
        glGetShaderInfoLog(shader, sizeof(compileMessage), nullptr, compileMessage);
        std::cout << "Shader compilation Info Log: " << compileMessage << std::endl;
#endif // LOG
        glDeleteShader(shader);
        return 0;
    }
}

GLuint TDW::Renderer::linkProgram(const std::vector<GLuint>& shaders, bool deleteShaders) {
    GLuint program = glCreateProgram();
    for (auto& shader : shaders) {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);

    if (deleteShaders) {
        for (auto& shader : shaders) {
            glDeleteShader(shader);
        }
    }
    
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    
    if (linkStatus == GL_TRUE) {
        return program;
    } else {
#ifdef LOG
        char linkMessage[512];
        glGetProgramInfoLog(program, sizeof(linkMessage), nullptr, linkMessage);
        std::cout << "Program link Info Log: " << linkMessage << std::endl;
#endif // LOG
        glDeleteProgram(program);
        return 0;
    }
}

void TDW::Renderer::disableVertexAttribute(GLuint program, std::string name) {
    auto location = glGetAttribLocation(program, name.c_str());
    glDisableVertexAttribArray(location);
}

void TDW::Renderer::enableVertexAttribute(GLuint program, std::string name, size_t size, size_t stride, int offset) {
    auto location = glGetAttribLocation(program, name.c_str());
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(location);
}

void TDW::Renderer::attachMatrix(GLuint program, std::string name, const glm::mat4& matrix) {
    GLint uniformLocation = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint TDW::Renderer::setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices) {
    GLuint vertexAO;
    glGenVertexArrays(1, &vertexAO); 
    glBindVertexArray(vertexAO);

    GLuint vertexBO;
    glGenBuffers(1, &vertexBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesData.size(), verticesData.data(), GL_STATIC_DRAW);

    GLuint elementsBO;
    glGenBuffers(1, &elementsBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), indices.data(), GL_STATIC_DRAW);

    return vertexAO;
}
