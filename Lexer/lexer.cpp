#include "lexer.hpp"
#include <iostream>

void Lexer::lex() {
	std::cout << "You are trying to Lex\n";
	 
	while(!eof()) {
		Token T;
		lexeme.clear();
		while(isspace(peek())) {
			ignore();
		}
		if(isdigit(peek())) {
			T.name = Decimal_Integer_Literal;
			if(peek() == '0') {
				accept();
			}
			switch(peek()) {
				case('x'):
				case('X'):
					T.name = Hexadecimal_Integer_Literal;
					accept();
					while(isxdigit(peek())) {
						accept();
					}
					break;
				case('b'):
				case('B'):
					T.name = Binary_Integer_Literal;
					accept();
					while((peek() == '0') || (peek() == '1')) {
						accept();
					}						
					break;
				default:
					while(isdigit(peek())) {
						accept();
					}
					if(peek() == '.') {
						T.name = Floating_Point_Literal;
						accept();
						while(isdigit(peek())) {
							accept();
						}
						if((peek() == 'E') || (peek() == 'e')) {
							accept();
							if((peek() == '+') || (peek() == '-')) {
								accept();
							}
						}
						while(isdigit(peek())) {
							accept();
						}
					}
					break;
			}
			print(T);
		}
		else if(isalpha(peek())) {
			while(isalnum(peek())) {
				lexeme += accept();
			}
			if(matchKeyword(T)) {
				print(T);
			}
			else {
				T.identifierIndex = symbols.matchSymbol(lexeme);
				T.name = Identifier;
				print(T);
			}
		}
		else {
			switch(peek()) {
				case('#'):
					while((peek() != '\n') && (!eof())) {
						ignore();
					}
					break;
				case('\''):
					accept();
					T.name = Character_Literal;
					while((peek() != '\'') && (!eof())) {
						T.charVal = accept();
					}
					if(peek() == '\'') {
						accept();
					}
					print(T);
					break;
				case('\"'):
					accept();
					T.name = String_Literal;
					while((peek() != '\"') && (!eof())) {
						T.strVal += accept();
					}
					if(peek() == '\"') {
						accept();
					}
					print(T);
					break;
				case('{'):
					T.name = Left_Brace;
					accept();
					print(T);
					break;
				case('}'):
					T.name = Right_Brace;
					accept();
					print(T);
					break;
				case('('):
					T.name = Left_Paren;
					accept();
					print(T);
					break;
				case(')'):
					T.name = Right_Paren;
					accept();
					print(T);
					break;
				case('['):
					T.name = Left_Bracket;
					accept();
					print(T);
					break;
				case(']'):
					T.name = Right_Bracket;
					accept();
					print(T);
					break;
				case(','):
					T.name = Comma;
					accept();
					print(T);
					break;
				case(';'):
					T.name = Semicolon;
					accept();
					print(T);
					break;					
				case(':'):
					T.name = Colon;
					accept();
					print(T);
					break;
				case('='):
					accept();
					if(peek() == '=')
					{
						accept();
						T.name = Relational_Operator;
					}
					else
					{
					T.name = Assignment_Operator;
					}
					print(T);
					break;
				case('!'):
					T.name = Relational_Operator;
					accept();
					if(peek() == '=') {
						accept();
					}
					else {
						//Throw error
					}
					print(T);
					break;
				case('<'):
					T.name = Relational_Operator;
					accept();
					if(peek() == '=') {
						accept();
					}
					print(T);
					break;
				case('>'):
					T.name = Relational_Operator;
					accept();
					if(peek() == '=') {
						accept();
					}
					print(T);
					break;
				case('+'):
					T.name = Arithmetic_Operator;
					accept();
					print(T);
					break;
				case('-'):
					T.name = Arithmetic_Operator;
					accept();
					print(T);
					break;
				case('*'):
					T.name = Arithmetic_Operator;
					accept();
					print(T);
					break;
				case('/'):
					T.name = Arithmetic_Operator;
					accept();
					print(T);
					break;
				case('%'):
					T.name = Arithmetic_Operator;
					accept();
					print(T);
					break;
				case('&'):
					T.name = Bitwise_Operator;
					accept();
					print(T);
					break;
				case('|'):
					T.name = Bitwise_Operator;
					accept();
					print(T);
					break;
				case('^'):
					T.name = Bitwise_Operator;
					accept();
					print(T);
					break;
				case('~'):
					T.name = Bitwise_Operator;
					accept();
					print(T);
					break;
				case('?'):
					T.name = Conditional_Operator;
					accept();
					print(T);
					break;				
				default:
					break;
			}
		}
	}
}
 
bool Lexer::eof() {
	//peek first to set the eof bit
	file.peek();
	return file.eof();
}
 
char Lexer::peek() {
	return file.peek();
}
 
char Lexer::accept() {
	// Add character to current token
	return file.get();
}
 
void Lexer::ignore() {
	// Get character and do nothing with it
	file.get();
}

bool Lexer::matchKeyword(Token& t) {
	it = keywords.begin();
	while(it != keywords.end()) {
		if(it->first == lexeme) {
			t.name = it->second;
			return true;
		}
		it++;
	}
	return false;
}

void Lexer::print(Token t) {
	switch(t.name) {
		case Left_Brace: std::cout << "<left-brace>" << "\n";
			break;
		case Right_Brace: std::cout << "<right-brace>" << "\n";
			break;
		case Left_Paren: std::cout << "<left-paren>" << "\n";
			break;
		case Right_Paren: std::cout << "<right-paren>" << "\n";
			break;
		case Left_Bracket: std::cout << "<left-bracket>" << "\n";
			break;
		case Right_Bracket: std::cout << "<right-bracket>" << "\n";
			break;
		case Comma: std::cout << "<comma>" << "\n";
			break;
		case Semicolon: std::cout << "<semicolon>" << "\n";
			break;
		case Colon: std::cout << "<colon>" << "\n";
			break;
		case Relational_Operator: std::cout << "<relational-operator>" << "\n";
			break;
		case Arithmetic_Operator: std::cout << "<arithmetic-operator>" << "\n";
			break;
		case Bitwise_Operator: std::cout << "<bitwise-operator>" << "\n";
			break;
		case Logical_Operator: std::cout << "<logical-operator>" << "\n";
			break;
		case Conditional_Operator: std::cout << "<conditional-operator>" << "\n";
			break;
		case Assignment_Operator: std::cout << "<assignment-operator>" << "\n";
			break;
		case Keyword_And: std::cout << "<and>" << "\n";
			break;
		case Keyword_Bool: std::cout << "<bool>" << "\n";
			break;
		case Keyword_Char: std::cout << "<char>" << "\n";
			break;
		case Keyword_Def: std::cout << "<def>" << "\n";
			break;
		case Keyword_Else: std::cout << "<else>" << "\n";
			break;
		case Keyword_False: std::cout << "<false>" << "\n";
			break;
		case Keyword_Float: std::cout << "<float>" << "\n";
			break;
		case Keyword_If: std::cout << "<if>" << "\n";
			break;
		case Keyword_Int: std::cout << "<int>" << "\n";
			break;
		case Keyword_Let: std::cout << "<let>" << "\n";
			break;
		case Keyword_Not: std::cout << "<not>" << "\n";
			break;
		case Keyword_Or: std::cout << "<or>" << "\n";
			break;
		case Keyword_True: std::cout << "<true>" << "\n";
			break;
		case Keyword_Var: std::cout << "<var>" << "\n";
			break;
		case Identifier:std::cout << "<identifier: " << symbols.matchSymbol(t.identifierIndex) << ">\n";
			break;
		case Decimal_Integer_Literal: std::cout << "<decimal-integer-literal>" << "\n";
			break;
		case Hexadecimal_Integer_Literal: std::cout << "<hexadecimal-integer-literal>" << "\n";
			break;
		case Binary_Integer_Literal: std::cout << "<binary-integer-literal>" << "\n";
			break;
		case Floating_Point_Literal: std::cout << "<floating-point-literal>" << "\n";
			break;
		case Boolean_Literal: std::cout << "<boolean-literal>" << "\n";
			break;
		case Character_Literal: std::cout << "<character-literal: '" << t.charVal << "'>\n";
			break;
		case String_Literal: std::cout << "<string-literal: \"" << t.strVal << "\">\n";
			break;
	}
}