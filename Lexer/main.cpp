#include <iostream>

#include "lexer.hpp"

int main() {
	Lexer L("Input.txt");
	L.lex();
	std::cout << "Hello World\n";
	return 0;
}