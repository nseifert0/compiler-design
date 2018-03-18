//Nicholas Seifert
//Compiler Design - Spring 2018
#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

class Parser {
	public:
		Parser(const char* filepath):lexer(filepath) {
			lexer.print(lexer.lex());
		}
	private:
		Lexer lexer;
};

#endif