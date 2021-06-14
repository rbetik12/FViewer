#pragma once
#include <cstdint>

enum class VertexParseType {
    VertUvNorm,
    VertUv,
    VertNorm,
    Vert
};

#pragma pack(1)
struct Vec3 {
    float x;
    float y;
    float z;
};

#pragma pack(1)
struct Vec2 {
    float x;
    float y;
};

#pragma pack(1)
struct VertexUVNormal {
    Vec3 vertex;
    Vec2 uv;
    Vec3 normal;
};

#pragma pack(1)
struct VertexUV {
    Vec3 vertex;
    Vec2 uv;
};

#pragma pack(1)
struct VertexNormal {
    Vec3 vertex;
    Vec3 normal;
};

#pragma pack(1)
struct ModelHeader {
    VertexParseType type;
    uint64_t vertexAmount;
    uint64_t indexAmount;
};
