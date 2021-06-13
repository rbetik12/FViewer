%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "main.cpp"
	extern FILE *yyin;
	extern char* yyval;
	extern int lineno;
	extern int yylex();
	void yyerror(char*);
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
		printf("Vertex: %f %f %f\n", $2, $3, $4);
	}
	;

normal:
	NORMAL FLOAT FLOAT FLOAT {
		printf("Normal: %f %f %f\n", $2, $3, $4);
	}
	;
	
uv:
	UV FLOAT FLOAT FLOAT {
		printf("UV: %f %f\n", $2, $3);
	}
	|
	UV FLOAT FLOAT {
		printf("UV: %f %f\n", $2, $3);
	}

face:
	FACE indexes
	;
	
indexes:
	index_type
	| indexes index_type
	;

index_type:
	INTEGER {
		printf("Vertex\n");
	}
	| INTEGER '/' INTEGER '/' INTEGER {
		printf("Vertex/UV/Normal\n");
	}
	| INTEGER '/' '/' INTEGER {
		printf("Vertex/Normal\n");
	}
	| INTEGER '/' INTEGER {
		printf("Vertex/UV\n");
	}
	;