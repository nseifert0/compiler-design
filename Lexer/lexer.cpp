#include "lexer.hpp"

#include <iostream>

 void Lexer::lex() {
	 std::cout << "You are trying to Lex\n";
	 char x;
	 
	 while(!eof()) {
		x = file.get();
		std::cout << x << "\n";
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
	 // token.add(file.get());
 }
 
 void Lexer::reject() {
	 // Get character and do nothing with it
	 file.get();
 }