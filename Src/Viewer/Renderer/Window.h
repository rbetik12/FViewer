#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(uint32_t width, uint32_t height, std::string windowName);

    bool IsShouldClose();

    void SwapBuffers();

    void ShutDown();

    void OnUpdate();

    GLFWwindow* GetWindow();

    uint32_t GetWidth();

    uint32_t GetHeight();

private:
    GLFWwindow* window = nullptr;
    uint32_t width;
    uint32_t height;

    struct WindowData {
        uint32_t width;
        uint32_t height;
    };

    WindowData data;
};