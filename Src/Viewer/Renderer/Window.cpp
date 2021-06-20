#include <glad/glad.h>
#include "Window.h"

Window::Window(uint32_t width, uint32_t height, std::string windowName) : width(width), height(height) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (!status) {
        exit(EXIT_FAILURE);
    }

    //glfwSwapInterval(1);

    data.width = width;
    data.height = height;
    glfwSetWindowUserPointer(window, &data);
}

bool Window::IsShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

void Window::ShutDown() {
    glfwDestroyWindow(window);
}

void Window::OnUpdate() {
    glfwPollEvents();
    SwapBuffers();
}

GLFWwindow* Window::GetWindow() {
    return window;
}

uint32_t Window::GetWidth() {
    return width;
}

uint32_t Window::GetHeight() {
    return height;
}
