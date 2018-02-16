#include "lexer.hpp"
#include <iostream>

void Lexer::lex() {
	std::cout << "You are trying to Lex\n";
	 
	while(!eof()) {
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
			T.print();
		}
		else if(isalpha(peek())) {
			T.name = Identifier;
			while(isalnum(peek())) {
				lexeme+=accept();
			}
			matchKeyword();
			T.print();
		}
		else {
			switch(peek()) {
				case('#'):
					while((peek() != '\n') && (!eof())) {
						ignore();
					}
					break;
				case('\''):
					
					break;
				case('\"'):
				
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
					T.print();
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
					T.print();
					break;
				case('<'):
					T.name = Relational_Operator;
					accept();
					if(peek() == '=') {
						accept();
					}
					T.print();
					break;
				case('>'):
					T.name = Relational_Operator;
					accept();
					if(peek() == '=') {
						accept();
					}
					T.print();
					break;
				case('+'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
					break;
				case('-'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
					break;
				case('*'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
					break;
				case('/'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
					break;
				case('%'):
					T.name = Arithmetic_Operator;
					accept();
					T.print();
					break;
				case('&'):
					T.name = Bitwise_Operator;
					accept();
					T.print();
					break;
				case('|'):
					T.name = Bitwise_Operator;
					accept();
					T.print();
					break;
				case('^'):
					T.name = Bitwise_Operator;
					accept();
					T.print();
					break;
				case('~'):
					T.name = Bitwise_Operator;
					accept();
					T.print();
					break;
				case('?'):
					T.name = Conditional_Operator;
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
 
char Lexer::accept() {
	// Add character to current token
	return file.get();
}
 
void Lexer::ignore() {
	// Get character and do nothing with it
	file.get();
}

void Lexer::matchKeyword() {
	it = keywords.begin();
	while(it != keywords.end()) {
		if(it->first == lexeme) {
			T.name = it->second;
		}
		it++;
	}
}

void Lexer::matchToTable() {
	//Check if current Lexeme matches a keyword
	
}