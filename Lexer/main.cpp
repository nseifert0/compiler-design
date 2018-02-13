#include <iostream>

#include "lexer.hpp"

int main() {
	Lexer L("Input.txt");
	L.lex();
	return 0;
}