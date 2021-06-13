NAME=test-obj-parser
CC=g++
CC_FLAGS=-std=c++17
all: build-parser

build-parser: parser.tab.cpp lexer.yy.c
	$(CC) $(CC_FLAGS) -o $(NAME) parser.tab.cpp lex.yy.c

parser.tab.cpp:
	bison -d -o parser.tab.cpp parser.y

lexer.yy.c:
	flex lexer.flex

clean:
	-del $(NAME).exe
	-del *.o
	-del parser.tab.*
	-del lex.yy.*
	