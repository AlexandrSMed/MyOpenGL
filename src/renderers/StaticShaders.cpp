#include "StaticShaders.h"

const char* const TDW::StaticShaders::vertex = R"glsl(
    #version 330 core
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    in vec3 aPos;
    in float aColorFactor;

    out float colorFactor;

    void main() {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
        colorFactor = aColorFactor;
    }
)glsl";

const char* const TDW::StaticShaders::fragment = R"glsl(
    #version 330 core
    uniform float decayFactor;

    in float colorFactor;

    out vec4 fragColor;

    void main() {
        fragColor = vec4(vec3(0.4, 0.8 * decayFactor, 0.2) * colorFactor, 1.0);
    }
)glsl";
