#pragma once

#include <cstdint>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    uint32_t id;
public:
    VertexArray();

    ~VertexArray();

    void Bind() const;

    void UnBind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
