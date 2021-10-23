#include "BasicShaders.h"

const char* const TDW::BasicShaders::vertex = R"glsl(
	#version 330 core
	in vec3 aPos;

	void main() {
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)glsl";

const char* const TDW::BasicShaders::fragment = R"glsl(
	#version 330 core
	out vec4 FragColor;

	void main() {
		FragColor = vec4(0.3f, 0.5f, 0.7f, 1.0f);
	}
)glsl";
