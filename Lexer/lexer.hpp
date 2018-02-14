#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

#include <fstream>

class Lexer {
	public:
		Lexer(const char* filepath)
			: file(filepath)
		{
		}
	
	void lex();
	bool eof();
	char peek();
	void accept();
	void ignore();
	void matchToTable();
	
	private:
		std::ifstream file;
		Token T;
};

#endif