#include "BasicShaders.h"

const char* const TDW::BasicShaders::vertex = R"glsl(
    #version 330 core
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    in vec3 aPos;
    in vec2 aTextCoord;

    out vec2 textCoord;

    void main() {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
        textCoord = aTextCoord;
    }
)glsl";

const char* const TDW::BasicShaders::fragment = R"glsl(
    #version 330 core
    uniform sampler2D textureOne;
    uniform sampler2D textureTwo;
    uniform float mixingColorAlpha;
    uniform float textureInterpolation;

    in vec2 textCoord;

    out vec4 fragColor;

    void main() {
        vec4 mixingColor = vec4(0.64, 0.96, 0.96, mixingColorAlpha);
        vec4 texture = mix(texture(textureOne, textCoord), texture(textureTwo, textCoord), textureInterpolation);
        texture.a -= mixingColorAlpha;
        fragColor = vec4(texture.rgb * texture.a + mixingColor.rgb * mixingColor.a, 1);
}
)glsl";
