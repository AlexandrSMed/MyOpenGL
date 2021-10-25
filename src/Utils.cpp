#include <sstream>
#include <iostream>
#include <random>
#include "Utils.h"

std::string TDW::Utils::messageFromGlStatusCode(GLenum statusCode) {
    std::stringstream stream;
    stream << "Status code: " << statusCode << ". ";
    switch (statusCode) {
    case GL_NO_ERROR:
        stream << "No error";
        break;
    case GL_INVALID_ENUM:
        stream << "Invalid enum specifider";
        break;
    case GL_INVALID_OPERATION:
        stream << "Invalid operation performed";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        stream << "Invalid framebuffer operation";
        break;
    case GL_OUT_OF_MEMORY:
        stream << "Out of memory exception";
        break;
    default:
        stream << "Error is undefined";
    }
    return stream.str();
}

double TDW::Utils::randomNumber(double min, double max) {
    static std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rd);
}
