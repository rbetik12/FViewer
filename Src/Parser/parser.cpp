#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "../Viewer/Util/timer.hpp"

extern FILE* yyin;

extern int yyparse();

extern std::vector<Vec3> vertexes;
extern std::vector<Vec3> normals;
extern std::vector<Vec2> uvs;
extern std::vector<int> indexes;
extern std::vector<VertexUVNormal> vtUvNormVec;
extern std::vector<VertexNormal> vtNormalVec;
extern uint64_t facesAmount;

VertexParseType type;

const char* GetModelNameFromFilePath(const char* filepath);

const char* GetModelFaceType();

void SerializeModel(const char* modelName);

int main(int argc, const char* argv[]) {
    const char* modelName;
    const char* modelFaceType;
    if (argc < 2) {
        fprintf(stderr, "obj-parser <obj file name>\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    {
        Timer timer;
        yyparse();
    }
    std::cout << "Successfully parsed file!" << std::endl;
    fclose(yyin);

    modelName = GetModelNameFromFilePath(argv[1]);
    modelFaceType = GetModelFaceType();

    std::cout << "Model face type is: " << modelFaceType << std::endl;

    {
        Timer timer;
        SerializeModel(modelName);
    }
    std::cout << "Successfully serialized " << modelName << "!" << std::endl;
    return 0;
}

const char* GetModelNameFromFilePath(const char* filepath) {
    size_t filepathLen = strlen(filepath);
    for (size_t i = filepathLen; i >= 0; i--) {
        if (filepath[i] == '/' || filepath[i] == '\\') {
            return filepath + i + 1;
        }
    }

    return filepath;
}

void SerializeModel(const char* modelName) {
    ModelHeader header;
    char modelNameBuffer[256];
    FILE* modelFile;
    snprintf(modelNameBuffer, 256, "%s.bin", modelName);

    modelFile = fopen(modelNameBuffer, "wb");

    if (!modelFile) {
        std::cerr << "Can't create serialized model file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    header.type = type;
    header.facesAmount = facesAmount;

    switch (type) {
        case VertexParseType::Vert:
            header.indexAmount = indexes.size();
            header.vertexAmount = vertexes.size();

            fwrite(&header, sizeof(header), 1, modelFile);
            fwrite(vertexes.data(), sizeof(Vec3), vertexes.size(), modelFile);
            fwrite(indexes.data(), sizeof(int), indexes.size(), modelFile);
            break;
        case VertexParseType::VertUvNorm:
            header.indexAmount = 0;
            header.vertexAmount = vtUvNormVec.size();

            fwrite(&header, sizeof(header), 1, modelFile);
            fwrite(vtUvNormVec.data(), sizeof(VertexUVNormal), vtUvNormVec.size(), modelFile);
            break;
        case VertexParseType::VertNorm:
            header.indexAmount = 0;
            header.vertexAmount = vtNormalVec.size();

            fwrite(&header, sizeof(header), 1, modelFile);
            fwrite(vtNormalVec.data(), sizeof(VertexNormal), vtNormalVec.size(), modelFile);
            break;
        case VertexParseType::VertUv:
            header.indexAmount = 0;
            header.vertexAmount = vertexes.size();

            fwrite(&header, sizeof(header), 1, modelFile);
            fwrite(vertexes.data(), sizeof(VertexUV), vertexes.size(), modelFile);
            break;
        default:
            std::cerr << "Unknown type!" << std::endl;
            break;
    }

    fclose(modelFile);
}

const char* GetModelFaceType() {
    switch (type) {
        case VertexParseType::Vert:
            return "Vertex";
        case VertexParseType::VertNorm:
            return "Vertex and normal";
        case VertexParseType::VertUv:
            return "Vertex and uv";
        case VertexParseType::VertUvNorm:
            return "Vertex, uv and normal";
        default:
            return "Unknown type";
    }
}