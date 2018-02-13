#include "lexer.hpp"
#include <iostream>

 void Lexer::lex() {
	 std::cout << "You are trying to Lex\n";
	 char x;
	 
	 while(!eof()) {
		switch(peek()) {
			case('4'):
				T.name = Decimal_Integer_Literal;
				accept();
				break;
			case('+'):
				T.name = Arithmetic_Operator;
				accept();
				break;
			case('5'):
				T.name = Decimal_Integer_Literal;
				accept();
				break;
			case(';'):
				T.name = Semicolon;
				accept();
				break;				
		}
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
 
 void Lexer::reject() {
	 // Get character and do nothing with it
	 file.get();
 }