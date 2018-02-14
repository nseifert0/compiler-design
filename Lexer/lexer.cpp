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
		}
		else if(isalpha(peek())) {
			T.name = Identifier;
		}
		else {
			switch(peek()) {
				case('{'):
					T.name = Left_Brace;
					break;
				case('}'):
					T.name = Right_Brace;
					break;
				case('('):
					T.name = Left_Paren;
					break;
				case(')'):
					T.name = Right_Paren;
					break;
				case('['):
					T.name = Left_Bracket;
					break;
				case(']'):
					T.name = Right_Bracket;
					break;
				case(','):
					T.name = Comma;
					break;
				case(';'):
					T.name = Semicolon;
					break;					
				case(':'):
					T.name = Colon;
					break;
				case('+'):
					T.name = Arithmetic_Operator;
					break;				
				default:
					break;
			}
		}
		
		accept();
		T.print();
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