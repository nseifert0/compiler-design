//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"
#include "codegen.hpp"

int main() {
	Parser parser("Input.txt");
	parser.parseType();
	return 0;
}