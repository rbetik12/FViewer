#include <cstdio>
#include <iostream>
#include "Deserializer.h"

Deserializer::Deserializer() {

}

Deserializer::~Deserializer() {
    fclose(file);
}

void Deserializer::Deserialize(const char* filename) {
    if (file) {
        fclose(file);
    }

    file = fopen(filename, "rb");

    if (!file) {
        std::cerr << "Can't open file " << filename << "!" << std::endl;
        exit(EXIT_FAILURE);
    }

    fread(&header, sizeof(header), 1, file);
}

std::pair<Vec3*, int*> Deserializer::GetData() const {
    Vec3* vertexes = new Vec3[header.vertexAmount];
    int* indexes = new int[header.indexAmount];

    fread(vertexes, sizeof(Vec3), header.vertexAmount, file);
    fread(indexes, sizeof(int), header.indexAmount, file);

    return std::pair<Vec3*, int*>(vertexes, indexes);
}
