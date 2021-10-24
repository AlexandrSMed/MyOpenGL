#include "BasicShaders.h"

const char* const TDW::BasicShaders::vertex = R"glsl(
	#version 330 core
	uniform mat4 modelMatrix;

	in vec3 aPos;
	in vec2 aTextCoord;

	out vec2 textCoord;

	void main() {
		gl_Position = modelMatrix * vec4(aPos, 1.0);
		textCoord = aTextCoord;
	}
)glsl";

const char* const TDW::BasicShaders::fragment = R"glsl(
	#version 330 core
	uniform sampler2D texture;

	in vec2 textCoord;

	out vec4 fragColor;

	void main() {
		fragColor = texture(texture, textCoord);
	}
)glsl";
