//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"


int main() {
	Parser P;
	Lexer L("Input.txt");
	while(!L.eof()) {
		L.print(L.lex());
	}
	return 0;
}