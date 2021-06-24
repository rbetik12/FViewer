#pragma once

#include <utility>
#include "type.h"

class Deserializer {
public:
    Deserializer();
    ~Deserializer();
    void Deserialize(const char* filename);
    inline VertexParseType GetDataType() const {
        return header.type;
    }

    std::pair<Vec3*, int*> GetData() const;
    std::pair<VertexUVNormal*, size_t> GetVertUvNormData() const;
    std::pair<size_t, size_t> GetAmount() const;
private:
    ModelHeader header;
    FILE* file = nullptr;
};

