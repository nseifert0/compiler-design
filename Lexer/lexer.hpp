#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

#include <fstream>
#include <map>
#include <string>

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
	void matchKeyword();
	void matchToTable();
	
	private:
		std::ifstream file;
		Token T;
		std::map<std::string, TokenName> keyWords;
		std::map<std::string, TokenName>::iterator it;
};

#endif