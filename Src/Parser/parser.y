%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "parser.cpp"
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
	}
	;

normal:
	NORMAL FLOAT FLOAT FLOAT {

	}
	;
	
uv:
	UV FLOAT FLOAT FLOAT {

	}
	|
	UV FLOAT FLOAT {

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

	}
	| INTEGER '/' INTEGER '/' INTEGER {

	}
	| INTEGER '/' '/' INTEGER {

	}
	| INTEGER '/' INTEGER {

	}
	;

%%

void yyerror (char* str) {
    fprintf(stderr, "Syntax error at line %d. %s\n", lineno, str);
    exit(1);
}