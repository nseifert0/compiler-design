//Nicholas Seifert
//Compiler Design - Spring 2018

#include "lexer.hpp"

int main() {
	Lexer L("Input.txt");
	while(!L.eof()) {
		L.print(L.lex());
	}
	return 0;
}