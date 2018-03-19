//Nicholas Seifert
//Compiler Design - Spring 2018

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
			keywords.insert(std::make_pair("const", Keyword_Const));
			keywords.insert(std::make_pair("def", Keyword_Def));
			keywords.insert(std::make_pair("else", Keyword_Else));
			keywords.insert(std::make_pair("false", Keyword_False));
			keywords.insert(std::make_pair("float", Keyword_Float));
			keywords.insert(std::make_pair("if", Keyword_If));
			keywords.insert(std::make_pair("int", Keyword_Int));
			keywords.insert(std::make_pair("let", Keyword_Let));
			keywords.insert(std::make_pair("not", Keyword_Not));
			keywords.insert(std::make_pair("or", Keyword_Or));
			keywords.insert(std::make_pair("return", Keyword_Return));
			keywords.insert(std::make_pair("true", Keyword_True));
			keywords.insert(std::make_pair("var", Keyword_Var));
			keywords.insert(std::make_pair("void", Keyword_Void));
			keywords.insert(std::make_pair("volatile", Keyword_Volatile));
			keywords.insert(std::make_pair("while", Keyword_While));
		}
	
	Token lex();
	bool eof();
	char peek();
	char accept();
	void ignore();
	bool matchKeyword(Token&);
	void print(Token);
	void printAsBinary(int);
	
	private:
		std::ifstream file;
		Symbols symbols;
		std::string lexeme;
		std::map<std::string, TokenName> keywords;
		std::map<std::string, TokenName>::iterator it;
};

#endif