#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include "BasicRenderer.h"
#include "BasicShaders.h"
#include "Utils.h"


#pragma region Private
void TDW::BasicRenderer::switchTexture() {

    if (textureSwitching) {
        double timeFactor = glfwGetTime() - textureSwitchDeltaTime;
        textureTransitionAlpha += static_cast<float>(pow(timeFactor, 4));
        auto colorAlphaLocation = glGetUniformLocation(shaderProgram, "mixingColorAlpha");
        if (textureTransitionAlpha < 1) {
            glUniform1f(colorAlphaLocation, textureTransitionAlpha);
        } else {
            auto indexIterator = [this] (unsigned index) -> unsigned {
                if (index == textureStack.size() - 1) {
                    return 0;
                } else {
                    return index + 1;
                }
            };

            activeTextureIndex = indexIterator(activeTextureIndex);
            auto nextTextureIndex = indexIterator(activeTextureIndex);

            auto textureOneLocation = glGetUniformLocation(shaderProgram, "textureOne");
            glUniform1i(textureOneLocation, activeTextureIndex);
            auto textureTwoLocation = glGetUniformLocation(shaderProgram, "textureTwo");
            glUniform1i(textureTwoLocation, nextTextureIndex);
            auto textureInterpolationLocation = glGetUniformLocation(shaderProgram, "textureInterpolation");
            glUniform1f(textureInterpolationLocation, static_cast<float>(Utils::randomNumber(0.5)));

            textureSwitching = false;
            textureSwitchDeltaTime = glfwGetTime();
        }
        
    } else if (textureTransitionAlpha > 0.008f) {
        double timeFactor = glfwGetTime() - textureSwitchDeltaTime;
        textureTransitionAlpha -= static_cast<float>(pow(timeFactor, 2));
        auto colorAlphaLocation = glGetUniformLocation(shaderProgram, "mixingColorAlpha");
        glUniform1f(colorAlphaLocation, textureTransitionAlpha);
    }
}

void TDW::BasicRenderer::slowboatTranformations() {
    float timeFrame = static_cast<float>(deltaTime);
    float angle = timeFrame * 8;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
}

void TDW::BasicRenderer::refreshDeltaTime() {
    auto currentTime = glfwGetTime();
    if (lastFrameTime > 0) {
        deltaTime = currentTime - lastFrameTime;
    }
    lastFrameTime = currentTime;
    return;
}

void TDW::BasicRenderer::setVertices(const std::vector<float>& verticesData, const std::vector<GLubyte>& indices) {
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
}

void TDW::BasicRenderer::attachTexture(std::string texturePath, int glTextureIndex) {
    int width, height;
    auto imageData = stbi_load(texturePath.c_str(), &width, &height, nullptr, 0);

    if (!imageData) {
#ifdef LOG
        std::cout << "Could not load texture from path: " << texturePath << std::endl;
#endif // LOG
        return;
    }
    
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(glTextureIndex);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
}

void TDW::BasicRenderer::applyTransformMatrix(std::string name, const glm::mat4& matrix) {
    GLint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void TDW::BasicRenderer::refreshProjectionMatrix() {
    GLint data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    projectionMatrix = glm::perspective(glm::radians(45.0f), float(data[2]) / float(data[3]), 2.0f, 100.0f);
}

#pragma endregion Private
    
void TDW::BasicRenderer::contextDidLoad(GLFWwindow*, int width, int height) {
    lastXMousePos = width / 2;
    lastYMousePos = height / 2;
    
    glEnable(GL_DEPTH_TEST);
    refreshProjectionMatrix();

    std::vector<GLuint> shaders {
        loadShader(GL_VERTEX_SHADER, BasicShaders::vertex),
        loadShader(GL_FRAGMENT_SHADER, BasicShaders::fragment)
    };
    shaderProgram = linkProgram(shaders);
    glUseProgram(shaderProgram);

    setVertices({
        // Vertices				// Texture	
        -0.5f,	-0.5f,	0.5f,	0.0f,	0.0f, // 0
        0.5f,	-0.5f,	0.5f,	1.0f,	0.0f, // 1
        0.5f,	0.5f,	0.5f,	1.0f,	1.0f, // 2
        -0.5f,	0.5f,	0.5f,	0.0f,	1.0f, // 3

        0.5f,	0.5f,	-0.5f,	0.0f,	1.0f, // 4
        0.5f,	-0.5,	-0.5f,	0.0f,	0.0f, // 5

        -0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f, // 6
        -0.5f,	0.5f,	-0.5f,	1.0f,	1.0f, // 7

        -0.5f,	0.5f,	0.5f,	1.0f,	0.0f, // 8
        -0.5f,	0.5f,	-0.5f,	0.0f,	0.0f, // 9

        -0.5f,	-0.5f,	0.5f,	1.0f,	1.0f, // 10
        -0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f  // 11
    }, {
        0,	1,	2,		0,	3,	2,
        1,	5,	4,		1,	2,	4,
        5,	6,	7,		5,	4,	7,
        2,	4,	9,		2,	8,	9,
        8,	9,	11,		8,	10,	11,
        1,	5,	10,		5,	11,	10
    });
    auto stride = sizeof(float) * 5;
    enableVertexAttribute(shaderProgram, "aPos", 3, stride, 0);
    enableVertexAttribute(shaderProgram, "aTextCoord", 2, stride, sizeof(float) * 3);
    for (size_t i = 0; i < textureStack.size(); ++i) {
        auto textureName = textureStack[i];
        attachTexture(textureName, GL_TEXTURE0 + static_cast<int>(i));
    }

    auto colorAlphaLocation = glGetUniformLocation(shaderProgram, "mixingColorAlpha");
    glUniform1f(colorAlphaLocation, textureTransitionAlpha);
    auto textureInterpolationLocation = glGetUniformLocation(shaderProgram, "textureInterpolation");
    glUniform1f(textureInterpolationLocation, 0);
    auto textureOneLocation = glGetUniformLocation(shaderProgram, "textureOne");
    glUniform1i(textureOneLocation, 0);
}

void TDW::BasicRenderer::draw(GLFWwindow*) {
    refreshDeltaTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switchTexture();
    slowboatTranformations();
    applyTransformMatrix("projectionMatrix", projectionMatrix);
    applyTransformMatrix("viewMatrix", camera.viewMatrix());
    applyTransformMatrix("modelMatrix", modelMatrix);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);


}

void TDW::BasicRenderer::mouseDidMove(GLFWwindow* window, double xPos, double yPos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        static const auto cameraSpeed = deltaTime * 16;

        float xDelta = static_cast<float>((xPos - lastXMousePos) * cameraSpeed);

        auto yRotationMatrix = glm::rotate(glm::mat4(1), -xDelta, glm::vec3(0, 1, 0));
        auto rotationResult = yRotationMatrix * glm::vec4(camera.cameraPosition, 1);
        camera.cameraPosition = glm::vec3(rotationResult);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        static const auto rotationSpeed = deltaTime * 16;
        float xDelta = static_cast<float>((xPos - lastXMousePos) * rotationSpeed);
        float yDelta = static_cast<float>((lastYMousePos - yPos) * rotationSpeed);

        modelMatrix = glm::rotate(modelMatrix, xDelta, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, yDelta, glm::vec3(1, 0, 0));

    }

    lastXMousePos = xPos;
    lastYMousePos = yPos;
}

void TDW::BasicRenderer::windowDidResize(GLFWwindow*, int, int) {
    refreshProjectionMatrix();
}

void TDW::BasicRenderer::keyDidSendAction(GLFWwindow*, int key, int action) {
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_SPACE) && !textureSwitching) {
        textureSwitching = true;
        textureSwitchDeltaTime = glfwGetTime();
    }
}

TDW::BasicRenderer::~BasicRenderer() {
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexAO);
}

