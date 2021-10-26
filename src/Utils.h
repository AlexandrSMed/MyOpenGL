#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TDW {
    namespace Utils {

        std::string messageFromGlStatusCode(GLenum statusCode);
        double randomNumber(double min = 0, double max = 1);
        double deltaTime(bool refresh = false);
    }
}
