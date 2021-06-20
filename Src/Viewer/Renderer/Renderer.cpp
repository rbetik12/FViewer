#include "Renderer.h"

void Renderer::LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount) {
    vertexBuffer = std::make_unique<VertexBuffer>(vertexes, vertexAmount * sizeof(Vec3));
    indexBuffer = std::make_unique<IndexBuffer>((uint32_t*)indexes, indexAmount);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
}

void Renderer::Run() {
    while(!window->IsShouldClose()) {
        glfwPollEvents();
        Renderer::Clear();

        vertexArray->Bind();
        indexBuffer->Bind();
        Draw(*vertexArray, *indexBuffer);
        window->SwapBuffers();
    }
}

Renderer::Renderer() {
    window = std::make_unique<Window>(800, 600, "FViewer");
    Renderer::Init();
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(117.0f / 256.0f, 170.0f / 256.0f, 1.0f, 1.0f);
}

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo) {
    glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}
