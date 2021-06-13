%option noyywrap

%{
	#include <stdlib.h>
	#include "parser.tab.hpp"
	extern FILE *yyin;
	
	int lineno = 1;
	void yyerror(char *);
%}

%%

#.* {
	lineno++;
};

[ \t\r\f]+ ;

^v {
	//printf("v\n");
    return VERTEX;
}

^vn {
	//printf("vn\n");
    return NORMAL;
}

^vt {
	//printf("vt\n");
    return UV;
}

^f {
	//printf("vf\n");
    return FACE;
}

^s.*$ {
    //printf("%s", yytext);
}

^g.*$ {
    //printf("%s", yytext);
}

^o.*$ {

}

^mtllib.*$ {
    //printf("%s", yytext);
}

^usemtl.*$ {
    //printf("%s", yytext);
}

[-+]?[0-9]+ {
    yylval.i = atoi(yytext);
	//printf("Integer\n");
    return INTEGER;
}

[-+]?[0-9]+\.?[0-9]+ {
    yylval.f = atof(yytext);
	//printf("Float\n");
    return FLOAT;
}

\/ {
    return '/';
}

\n {
    lineno++;
};

. {
	char errMsgBuf[256];
	snprintf(errMsgBuf, 256, "Unknown character %s", yytext);
	yyerror(errMsgBuf);
};

%%