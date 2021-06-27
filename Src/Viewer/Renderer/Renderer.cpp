#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>
#include "Renderer.h"
#include "Shader.h"
#include "../../Debug/Debug.h"
#include "Light.h"
#include "../Input/Input.h"
#include "../Input/Time.h"
#include "../Camera/Camera.h"
#include "../UI/UI.h"

void Renderer::LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, vertexAmount * sizeof(Vec3));
    indexBuffer = std::make_unique<IndexBuffer>((uint32_t*)indexes, indexAmount);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
    type = VertexParseType::Vert;
}

void Renderer::LoadData(VertexUVNormal* vertexes, size_t amount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, amount * sizeof(VertexUVNormal));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
    type = VertexParseType::VertUvNorm;
}

void Renderer::LoadData(VertexNormal* vertexes, size_t amount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, amount * sizeof(VertexUVNormal));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
    type = VertexParseType::VertNorm;
}

void Renderer::Run() {
    Shader* shader = nullptr;
    switch(type) {
        case VertexParseType::VertNorm:
            shader = new Shader("vertex_norm.vert", "vertex_norm.frag");
            break;
        case VertexParseType::VertUvNorm:
            shader = new Shader("vertex_uv_norm.vert", "vertex_uv_norm.frag");
            break;
    }
    Light light;
    Camera camera(glm::vec3(0, 2, 10), glm::vec3(0, 1, 0));
    OpenGLDebug::Init();
    Input::Init(*window);
    UI* ui = UI::Create(window.get());

    while (!window->IsShouldClose()) {
        glfwPollEvents();
        Clear();
        Time::Update();
        camera.Update();

        if (Input::GetKeyDown(GLFW_KEY_M)) {
            Input::ToggleCursor(*window);
        }
        auto newLightDir = glm::vec3(10 * sin(glfwGetTime()), 5 * cos(glfwGetTime()), 0);
        light.SetDirection(newLightDir);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (GLfloat) window->GetWidth() / (GLfloat) window->GetHeight(), 0.1f, 300.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, 0));
        model = glm::scale(model, glm::vec3(1, 1, 1));
        shader->Bind();
        shader->SetUniformMat4f("projection", projection);
        shader->SetUniformMat4f("view", camera.GetViewMatrix());
        shader->SetUniformMat4f("model", model);
        shader->SetUniform3f("directionalLight.direction", light.GetDirection().x,
                                 light.GetDirection().y,
                                 light.GetDirection().z);
        shader->SetUniform3f("directionalLight.ambient", light.GetAmbientColor().x,
                                 light.GetAmbientColor().y,
                                 light.GetAmbientColor().z);
        shader->SetUniform3f("directionalLight.diffuse", light.GetDiffuseColor().x,
                                 light.GetDiffuseColor().y,
                                 light.GetDiffuseColor().z);
        shader->SetUniform3f("viewPos", camera.GetPosition());
        if (indexBuffer == nullptr) {
            Draw(*vertexArray, *vertexBuffer, *shader);
        }
        else {
            Draw(*vertexArray, *indexBuffer, *shader);
        }

        ui->Begin();
        {
            ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
            ImGui::Begin("Debug");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ui->End();
        window->SwapBuffers();
    }

    delete shader;
}

Renderer::Renderer() {
    window = std::make_unique<Window>(1920, 1080, "FViewer");
    Init();
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) {
    vao.Bind();
    ebo.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo, const Shader& shader) {
    vao.Bind();
    vbo.Bind();
    shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, vbo.GetSize());
}
