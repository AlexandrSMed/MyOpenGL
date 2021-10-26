#include <iostream>
#include <algorithm>
#include <iterator>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.h"
#include "StaticShaders.h"
#include "StaticRenderer.h"

TDW::StaticRenderer::StaticRenderer(size_t count, unsigned radius) {

    std::generate_n(std::back_inserter(modelMatrices), count, [radius] {
        glm::mat4 modelMatrix(1.0f);

        double randomHypo = static_cast<double>(radius) * pow(Utils::randomNumber(), 1.0 / 3.2);
        double randomAngle = Utils::randomNumber() * 2 * glm::pi<double>();
        float x = static_cast<float>(randomHypo * cos(randomAngle));
        float z = static_cast<float>(randomHypo * sin(randomAngle));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0, z));

        float pitch = static_cast<float>(Utils::randomNumber(-16, 16));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(pitch), glm::vec3(1, 0, 0));
        float yaw = static_cast<float>(Utils::randomNumber(-16, 16));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(yaw), glm::vec3(0, 1, 0));
        float roll = static_cast<float>(Utils::randomNumber(-16, 16));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(roll), glm::vec3(0, 0, 1));

        float yScale = static_cast<float>(Utils::randomNumber(0.5, 1.5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, yScale, 1));

        float decayFactor = static_cast<float>(Utils::randomNumber());
        return std::make_pair(modelMatrix, decayFactor);
    });
}

void TDW::StaticRenderer::draw(GLFWwindow*, const Camera& camera) {
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexAO);
    attachMatrix(shaderProgram, "projectionMatrix", camera.projectionMatrix());
    attachMatrix(shaderProgram, "viewMatrix", camera.viewMatrix());

    for (auto& element : modelMatrices) {
        attachMatrix(shaderProgram, "modelMatrix", element.first);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, nullptr);
        auto decayFactorLocation = glGetUniformLocation(shaderProgram, "decayFactor");
        glUniform1f(decayFactorLocation, element.second);
    }
}

void TDW::StaticRenderer::contextDidLoad(GLFWwindow*, const Camera&, int, int) {
    glEnable(GL_DEPTH_TEST);

    std::vector<GLuint> shaders { 
        loadShader(GL_VERTEX_SHADER, StaticShaders::vertex),
        loadShader(GL_FRAGMENT_SHADER, StaticShaders::fragment)
    };
    shaderProgram = linkProgram(shaders);
    glUseProgram(shaderProgram);

    vertexAO = setVertices({
        // Vertex
        0.0f,   -0.6f,  0.2f,   0.4f, // 0
        0.2f,   -0.6f,  -0.2f,  0.4f, // 1  
        -0.2f,  -0.6f,  -0.2f,  0.4f, // 2
        0.0f,   0.2f,   0.0f,   1.0f // 3
    }, {
        0, 1, 2,
        1, 2, 3,
        1, 0, 3,
        2, 0, 3
    });
    auto stride = sizeof(float) * 4;
    enableVertexAttribute(shaderProgram, "aPos", 3, stride, 0);
    enableVertexAttribute(shaderProgram, "aColorFactor", 1, stride, sizeof(float) * 3);
}

void TDW::StaticRenderer::mouseDidMove(GLFWwindow*, const Camera&, double, double) {}

void TDW::StaticRenderer::windowDidResize(GLFWwindow*, const Camera&, int, int) {}

void TDW::StaticRenderer::keyDidSendAction(GLFWwindow*, const Camera&, int, int) {}

TDW::StaticRenderer::~StaticRenderer() {}
