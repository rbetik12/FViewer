#pragma once

#include <type.h>
#include <memory>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Window.h"

class Renderer {
public:
    Renderer();

    void LoadData(Vec3* vertexes, int* indexes, size_t vertexAmount, size_t indexAmount);
    void Run();

private:
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;
    std::unique_ptr<VertexArray> vertexArray;
    std::unique_ptr<Window> window;

    static void Init();
    static void Clear();
    void Draw(const VertexArray& vao, const IndexBuffer& ebo);
};
