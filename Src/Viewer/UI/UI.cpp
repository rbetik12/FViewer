#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

#include "UI.h"
#include "../Renderer/Window.h"

UI* UI::Create(Window* window) {
    if (!instance) {
        instance = new UI(window);
    }
    return instance;
}

UI::~UI() {

}

void UI::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::End() {
    ImGui::Render();
    int displayW, displayH;
    glfwGetFramebufferSize(window->GetWindow(), &displayW, &displayH);
    glViewport(0, 0, displayW, displayH);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::UI(Window* _window) {
    window = _window;
    Init(_window);
}

void UI::Init(Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

UI* UI::instance = nullptr;
Window* UI::window = nullptr;
