#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include "symbols.hpp"

#include <fstream>
#include <map>
#include <string>

class Lexer {
	public:
		Lexer(const char* filepath)
			: file(filepath)
		{
			keywords.insert(std::make_pair("and", Keyword_And));
			keywords.insert(std::make_pair("bool", Keyword_Bool));
			keywords.insert(std::make_pair("char", Keyword_Char));
			keywords.insert(std::make_pair("def", Keyword_Def));
			keywords.insert(std::make_pair("else", Keyword_Else));
			keywords.insert(std::make_pair("false", Keyword_False));
			keywords.insert(std::make_pair("float", Keyword_Float));
			keywords.insert(std::make_pair("if", Keyword_If));
			keywords.insert(std::make_pair("int", Keyword_Int));
			keywords.insert(std::make_pair("let", Keyword_Let));
			keywords.insert(std::make_pair("not", Keyword_Not));
			keywords.insert(std::make_pair("or", Keyword_Or));
			keywords.insert(std::make_pair("true", Keyword_True));
			keywords.insert(std::make_pair("var", Keyword_Var));
		}
	
	void lex();
	bool eof();
	char peek();
	char accept();
	void ignore();
	bool matchKeyword();
	void print(Token);
	
	private:
		std::ifstream file;
		Token T;
		Symbols symbols;
		std::string lexeme;
		std::map<std::string, TokenName> keywords;
		std::map<std::string, TokenName>::iterator it;
};

#endif