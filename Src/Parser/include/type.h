#pragma once
#include <cstdint>

#pragma pack(push, 1)
enum class VertexParseType {
    VertUvNorm,
    VertUv,
    VertNorm,
    Vert
};

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Vec2 {
    float x;
    float y;
};

struct VertexUVNormal {
    Vec3 vertex;
    Vec2 uv;
    Vec3 normal;
};

struct VertexUV {
    Vec3 vertex;
    Vec2 uv;
};

struct VertexNormal {
    Vec3 vertex;
    Vec3 normal;
};

struct ModelHeader {
    VertexParseType type;
    uint64_t vertexAmount;
    uint64_t indexAmount;
};
#pragma pack(pop)