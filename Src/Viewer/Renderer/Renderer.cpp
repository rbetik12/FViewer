#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "../../Debug/Debug.h"

void Renderer::LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, vertexAmount * sizeof(Vec3));
    indexBuffer = std::make_unique<IndexBuffer>((uint32_t*)indexes, indexAmount);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
}

void Renderer::LoadData(VertexUVNormal* vertexes, size_t amount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, amount * sizeof(VertexUVNormal));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
}

void Renderer::Run() {
    Shader shader("vertex_uv_norm.vert", "vertex_uv_norm.frag");

    OpenGLDebug::Init();

    while (!window->IsShouldClose()) {
        glfwPollEvents();
        Clear();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (GLfloat) window->GetWidth() / (GLfloat) window->GetHeight(), 0.1f, 300.0f);
        glm::mat4 view = glm::lookAt(
                glm::vec3(10, 10, 3),
                glm::vec3(0, 0, 0),
                glm::vec3(0, 1, 0)
        );

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, 0));
        model = glm::rotate(model, glm::radians(50.0f * (float) glfwGetTime()), glm::vec3(0.0f, 0, 1.0f));
        model = glm::scale(model, glm::vec3(1, 1, 1));
        shader.Bind();
        shader.SetUniformMat4f("projection", projection);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("model", model);

        if (indexBuffer == nullptr) {
            Draw(*vertexArray, *vertexBuffer, shader);
        }
        else {
            Draw(*vertexArray, *indexBuffer, shader);
        }
        window->SwapBuffers();
    }
}

Renderer::Renderer() {
    window = std::make_unique<Window>(800, 600, "FViewer");
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
