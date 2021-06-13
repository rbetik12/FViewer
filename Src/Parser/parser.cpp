#include <stdio.h>
#include <cstdlib>

extern FILE* yyin;
extern int yyparse();

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "test-obj-parser <obj file name>\n");
		exit(1);
	}
	
    int flag;
    yyin = fopen(argv[1], "r");
    flag = yyparse();
    fclose(yyin);

    return flag;
}