#pragma once
#include <string>
#include <glad/glad.h>

namespace TDW {
    namespace Utils {

        std::string messageFromGlStatusCode(GLenum statusCode);
        double randomNumber(double min = 0, double max = 1);
    }
}
