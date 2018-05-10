//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"
#include "codegen.hpp"

extern "C" int main(int argc, char* argv[]) {
	Parser parser("Input.txt");
	Decl* myProgram = parser.parseProgram();
	generate(myProgram);
	return 0;
}