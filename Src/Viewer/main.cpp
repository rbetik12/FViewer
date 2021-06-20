#include <iostream>
#include "Deserialize/Deserializer.h"
#include "Renderer/Renderer.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
	    std::cerr << "FViewer <obj.bin file path>" << std::endl;
	}

	Deserializer deserializer;
	deserializer.Deserialize(argv[1]);

	Renderer renderer;

    switch (deserializer.GetDataType()) {
        case VertexParseType::VertUvNorm:
            break;
        case VertexParseType::VertUv:
            break;
        case VertexParseType::VertNorm:
            break;
        case VertexParseType::Vert:
            Vec3* vertexes = nullptr;
            int* indexes = nullptr;
            size_t vertexAmount, indexAmount;

            std::pair<Vec3*, int*> data = deserializer.GetData();
            std::pair<size_t, size_t> amount = deserializer.GetAmount();
            vertexes = data.first;
            indexes = data.second;
            vertexAmount = amount.first;
            indexAmount = amount.second;

            renderer.LoadData(vertexes, indexes, vertexAmount, indexAmount);
            renderer.Run();

            delete [] vertexes;
            delete [] indexes;
            break;
    }
	return 0;
}