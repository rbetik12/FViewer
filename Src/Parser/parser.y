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
	;

normal:
	NORMAL FLOAT FLOAT FLOAT {
        normals.push_back({$2, $3, $4});
	}
	;
	
uv:
	UV FLOAT FLOAT FLOAT {
        uvs.push_back({$2, $3});
	}
	|
	UV FLOAT FLOAT {
        uvs.push_back({$2, $3});
	}

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
	}
	// vertex / normal
	| INTEGER '/' '/' INTEGER {
        type = VertexParseType::VertNorm;
	}
	// vertex / uv
	| INTEGER '/' INTEGER {
        type = VertexParseType::VertUv;
	}
	;

%%

void yyerror (char* str) {
    fprintf(stderr, "Syntax error at line %d. %s\n", lineno, str);
    exit(1);
}