#include <iostream>
#include "Deserialize/Deserializer.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
	    std::cerr << "FViewer <obj.bin file path>" << std::endl;
	}

	Deserializer deserializer;
	deserializer.Deserialize(argv[1]);

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

            std::pair<Vec3*, int*> data = deserializer.GetData();
            vertexes = data.first;
            indexes = data.second;

            delete [] vertexes;
            delete [] indexes;
            break;
    }
	return 0;
}