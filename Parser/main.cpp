#include <stdio.h>
#include <cstdlib>

extern int lineno;
extern FILE* yyin;

int yyparse();

void yyerror (char* str) {
    fprintf(stderr, "Syntax error at line %d. %s\n", lineno, str);
    exit(1);
}

int main (int argc, char *argv[]) {
    int flag;
    yyin = fopen("box.obj", "r");
    flag = yyparse();
    fclose(yyin);

    return flag;
}