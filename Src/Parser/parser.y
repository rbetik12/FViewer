%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <vector>
	#include "type.h"
	#include "parser.cpp"
	extern FILE *yyin;
	extern char* yyval;
	extern int lineno;
	extern int yylex();
	extern VertexParseType type;
	void yyerror(char*);

	std::vector<Vec3> vertexes;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<int> indexes;
    std::vector<VertexUVNormal> vtUvNormVec;
    std::vector<VertexUV> vtUvVec;
    std::vector<VertexNormal> vtNormalVec;
%}

%start obj

%union {
	int i;
	float f;
}

%token VERTEX NORMAL UV FACE INTEGER FLOAT

%type<i> INTEGER
%type<f> FLOAT

%%
obj:
	objcmd
	| obj objcmd
	;

objcmd:
	vertex
	| normal
	| uv
	| face
	;
	
vertex:
	VERTEX FLOAT FLOAT FLOAT {
	    vertexes.push_back({$2, $3, $4});
	}
	|
	VERTEX FLOAT FLOAT INTEGER {
    	vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX FLOAT INTEGER FLOAT {
        vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX FLOAT INTEGER INTEGER {
        vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX INTEGER FLOAT FLOAT {
        vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX INTEGER FLOAT INTEGER {
        vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX INTEGER INTEGER FLOAT {
        vertexes.push_back({$2, $3, $4});
    }
    |
    VERTEX INTEGER INTEGER INTEGER {
        vertexes.push_back({$2, $3, $4});
    }
    |
	;

normal:
	NORMAL FLOAT FLOAT FLOAT {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL FLOAT FLOAT INTEGER {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL FLOAT INTEGER FLOAT {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL FLOAT INTEGER INTEGER {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL INTEGER FLOAT FLOAT {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL INTEGER FLOAT INTEGER {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL INTEGER INTEGER FLOAT {
        normals.push_back({$2, $3, $4});
    }
    |
    NORMAL INTEGER INTEGER INTEGER {
        normals.push_back({$2, $3, $4});
    }
    |
    ;
	
uv:
	UV FLOAT FLOAT FLOAT {
        uvs.push_back({$2, $3});
	}
	|
	UV FLOAT FLOAT {
        uvs.push_back({$2, $3});
	}
	|
	UV FLOAT INTEGER {
        uvs.push_back({$2, $3});
    }
    |
    UV INTEGER FLOAT {
        uvs.push_back({$2, $3});
    }
    |
    UV INTEGER INTEGER {
        uvs.push_back({$2, $3});
    }
    |
	;

face:
	FACE indexes
	;

indexes:
	index_type
	| indexes index_type
	;

index_type:
    // vertex
	INTEGER {
        type = VertexParseType::Vert;
        indexes.push_back($1 - 1);
	}
	// vertex / uv / normal
	| INTEGER '/' INTEGER '/' INTEGER {
        type = VertexParseType::VertUvNorm;
        VertexUVNormal vertex;
        vertex.vertex = vertexes[$1 - 1];
        vertex.uv = uvs[$3 - 1];
        vertex.normal = normals[$5 - 1];
        vtUvNormVec.push_back(vertex);
	}
	// vertex / normal
	| INTEGER '/' '/' INTEGER {
        type = VertexParseType::VertNorm;
        VertexNormal vertex;
        vertex.vertex = vertexes[$1 - 1];
        vertex.normal = normals[$4 - 1];
        vtNormalVec.push_back(vertex);
	}
	// vertex / uv
	| INTEGER '/' INTEGER {
        type = VertexParseType::VertUv;
        VertexUV vertex;
        vertex.vertex = vertexes[$1 - 1];
        vertex.uv = uvs[$3 - 1];
        vtUvVec.push_back(vertex);
	}
	;

%%

void yyerror (char* str) {
    fprintf(stderr, "Syntax error at line %d. %s\n", lineno, str);
    exit(1);
}