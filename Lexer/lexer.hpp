#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>

class Lexer {
	public:
		Lexer(const char* path)
			: file(path)
		{
		}
	
	void lex();
	bool eof();
	char peek();
	
	private:
		std::ifstream file;
};

#endif