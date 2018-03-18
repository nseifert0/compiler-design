//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

#include <deque>

class Parser {
	public:
		Parser(const char* filepath):lexer(filepath) {
		}
		
		void pushToken();
		void parse();
	private:
		Lexer lexer;
		std::deque<Token> tokenQueue;
};

#endif