#include <cstdio>
#include <iostream>
#include "Debug.h"

void OpenGLDebug::Init() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLErrorCallback, nullptr);
}

void OpenGLDebug::GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                                  const void* userParam) {
    char* outputMsg = new char[512];
    snprintf(outputMsg, 512, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
             type, severity, message);

    std::cerr << outputMsg << std::endl;
}