#ifndef LEXER_HPP
#define LEXER_HPP

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
	void reject();
	
	private:
		std::ifstream file;
};

#endif