#pragma once

#include <type.h>
#include <memory>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Window.h"
#include "Shader.h"

class Renderer {
public:
    Renderer();

    void LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount);
    void LoadData(VertexUVNormal* vertexes, size_t amount);
    void LoadData(VertexNormal* vertexes, size_t amount);

    void Run();
    uint64_t faces;
    uint64_t vertexes;
private:
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;
    std::unique_ptr<VertexArray> vertexArray;
    std::unique_ptr<Window> window;

    void Init();

    void Clear();

    void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader);
    void Draw(const VertexArray& vao, const VertexBuffer& vbo, const Shader& shader);
    VertexParseType type;
    bool isLight = true;
    bool rotateLight = true;
};
