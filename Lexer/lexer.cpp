#include "lexer.hpp"
#include <iostream>

void Lexer::lex() {
	std::cout << "You are trying to Lex\n";
	 
	while(!eof()) {
		while(isspace(peek())) {
			ignore();
		}
		if(isdigit(peek())) {
			T.name = Decimal_Integer_Literal;
			accept();
			T.print();
		}
		else if(isalpha(peek())) {
			T.name = Identifier;
			accept();
			T.print();
		}
		else {
			switch(peek()) {
				case('#'):
					while((peek() != '\n') && !eof())
					{
						ignore();
					}
					break;
				case('{'):
					T.name = Left_Brace;
					accept();
					T.print();
					break;
				case('}'):
					T.name = Right_Brace;
					accept();
					T.print();
					break;
				case('('):
					T.name = Left_Paren;
					accept();
					T.print();
					break;
				case(')'):
					T.name = Right_Paren;
					accept();
					T.print();
					break;
				case('['):
					T.name = Left_Bracket;
					accept();
					T.print();
					break;
				case(']'):
					T.name = Right_Bracket;
					accept();
					T.print();
					break;
				case(','):
					T.name = Comma;
					accept();
					T.print();
					break;
				case(';'):
					T.name = Semicolon;
					accept();
					T.print();
					break;					
				case(':'):
					T.name = Colon;
					accept();
					T.print();
					break;
				case('+'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
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
 
void Lexer::accept() {
	// Add character to current token
	file.get();
}
 
void Lexer::ignore() {
	// Get character and do nothing with it
	file.get();
}