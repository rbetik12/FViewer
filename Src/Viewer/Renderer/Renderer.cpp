#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "../../Debug/Debug.h"

void Renderer::LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount) {
    float triangleVertices[] = {
            -0.5, -0.5, 0,
            0, 0.5, 0,
            0.5, -0.5, 0
    };

    unsigned int triangleIndexes[] = {
            0, 1, 2
    };

    vertexBuffer = std::make_unique<VertexBuffer>(triangleVertices, sizeof(triangleVertices));
    indexBuffer = std::make_unique<IndexBuffer>(triangleIndexes, sizeof(triangleIndexes) / sizeof(uint32_t));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vertexArray = std::make_unique<VertexArray>();
    vertexArray->AddBuffer(*vertexBuffer, layout);
}

void Renderer::Run() {
    Shader shader("basic.vert", "basic.frag");

    OpenGLDebug::Init();

    while(!window->IsShouldClose()) {
        glfwPollEvents();
        Renderer::Clear();

        /*glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (GLfloat)window->GetWidth() / (GLfloat)window->GetHeight(), 0.1f, 300.0f);
        glm::mat4 view = glm::lookAt(
                glm::vec3(4, 3, 3),
                glm::vec3(0, 0, 0),
                glm::vec3(0, 1, 0)
                );

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, 0));

        shader.Bind();
        shader.SetUniformMat4f("projection", projection);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("model", model);
        vertexArray->Bind();
        indexBuffer->Bind();*/

        Draw(*vertexArray, *indexBuffer, shader);
        window->SwapBuffers();
    }
}

Renderer::Renderer() {
    window = std::make_unique<Window>(800, 600, "FViewer");
    Renderer::Init();
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Init() {
//    glEnable(GL_DEPTH_TEST);
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
