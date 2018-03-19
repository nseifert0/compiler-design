//Nicholas Seifert
//Compiler Design - Spring 2018

#include "lexer.hpp"
#include <iostream>
#include <sstream>
#include <bitset>

Token Lexer::lex() {
	Token t;
	lexeme.clear();
	
	while(isspace(peek())) {
		ignore();
	}
	
	//Set the location at the start of the token
	t.location = file.tellg();
	
	//Lex decimal/floating point literals
	if(isdigit(peek())) {
		if(peek() == '0') {
			accept();
		}
		switch(peek()) {
			case('x'):
			case('X'):
				t.name = Hexadecimal_Integer_Literal;
				accept();
				while(isxdigit(peek())) {
					lexeme+=accept();
				}
				t.integerValue = std::stoi(lexeme,nullptr,16);
				break;
			case('b'):
			case('B'):
				t.name = Binary_Integer_Literal;
				accept();
				while((peek() == '0') || (peek() == '1')) {
					lexeme+=accept();
				}
				t.integerValue = std::stoi(lexeme,nullptr,2);
				break;
			default:
				while(isdigit(peek())) {
					lexeme+=accept();
				}
				if(peek() == '.') {
					t.name = Floating_Point_Literal;
					lexeme+=accept();
					while(isdigit(peek())) {
						lexeme+=accept();
					}
					if((peek() == 'E') || (peek() == 'e')) {
						lexeme+=accept();
						if((peek() == '+') || (peek() == '-')) {
							lexeme+=accept();
						}
					}
					while(isdigit(peek())) {
						lexeme+=accept();
					}
					t.floatValue = std::stod(lexeme);
				}
				else {
					t.name = Decimal_Integer_Literal;
					t.integerValue = std::stoi(lexeme,nullptr,10);
				}
				break;
		}
	}
	
	//Lex words, identifiers, and other characters
	else if(isalpha(peek())) {
		while(isalnum(peek()) || peek() == '_') {
			lexeme += accept();
		}
		if(matchKeyword(t)) {
			switch(t.name) {
				case(Keyword_And):
					t.name = Logical_Operator;
					t.lot = And;
					break;
				case(Keyword_Or):
					t.name = Logical_Operator;
					t.lot = Or;
					break;
				case(Keyword_Not):
					t.name = Logical_Operator;
					t.lot = Not;
					break;
				case(Keyword_True):
					t.name = Boolean_Literal;
					t.blt = True;
					break;
				case(Keyword_False):
					t.name = Boolean_Literal;
					t.blt = False;
					break;						
			}
		}
		else {
			t.symbolTableIndex = symbols.matchSymbol(lexeme);
			t.name = Identifier;
		}
	}
	else {
		switch(peek()) {
			
			//Lex comments
			case('#'):
				while((peek() != '\n') && (!eof())) {
					ignore();
				}
				break;
			
			//Lex character literal
			case('\''):
				accept();
				if((peek() == '\''))
				{
					std::stringstream ss;
					ss << "empty character";
					throw std::runtime_error(ss.str());
				}				
				t.name = Character_Literal;
				if(peek() == '\\') {
					accept();
					switch(peek()) {
						case('\''):
							t.charVal = '\'';
							break;
						case('\"'):
							t.charVal = '\"';
							break;
						case('\\'):
							t.charVal = '\\';
							break;
						case('a'):
							t.charVal = '\a';
							break;
						case('b'):
							t.charVal = '\b';
							break;
						case('f'):
							t.charVal = '\f';
							break;
						case('n'):
							t.charVal = '\n';
							break;
						case('r'):
							t.charVal = '\r';
							break;
						case('t'):
							t.charVal = '\t';
							break;
						case('v'):
							t.charVal = '\v';
							break;
						default:
							std::stringstream ss;
							ss << "invalid escape character";
							throw std::runtime_error(ss.str());
							break;
					}
					accept();
				}
				while((peek() != '\'') && (!eof())) {
					t.charVal = accept();
				}
				if(peek() == '\'') {
					accept();
				}
				else{
					std::stringstream ss;
					ss << "unended character";
					throw std::runtime_error(ss.str());
				}
				break;
			
			//Lex string literal
			case('\"'):
				accept();
				t.name = String_Literal;
				while((peek() != '\"') && (!eof())) {
					lexeme += accept();
					t.symbolTableIndex = symbols.matchSymbol(lexeme);
				}
				if(peek() == '\"') {
					accept();
				}
				break;
				
			//Lex other kinds of tokens
			case('{'):
				t.name = Left_Brace;
				accept();
				break;
			case('}'):
				t.name = Right_Brace;
				accept();
				break;
			case('('):
				t.name = Left_Paren;
				accept();
				break;
			case(')'):
				t.name = Right_Paren;
				accept();
				break;
			case('['):
				t.name = Left_Bracket;
				accept();
				break;
			case(']'):
				t.name = Right_Bracket;
				accept();
				break;
			case(','):
				t.name = Comma;
				accept();
				break;
			case(';'):
				t.name = Semicolon;
				accept();
				break;					
			case(':'):
				t.name = Colon;
				accept();
				break;
			case('='):
				accept();
				if(peek() == '=')
				{
					accept();
					t.name = Relational_Operator;
					t.rot = Equal;
				}
				else
				{
					t.name = Assignment_Operator;
				}
				break;
			case('!'):
				t.name = Relational_Operator;
				accept();
				if(peek() == '=') {
					accept();
					t.rot = Not_Equal;
				}
				else {
					std::stringstream ss;
					ss << "! does not match a valid token";
					throw std::runtime_error(ss.str());
				}
				break;
			case('<'):
				accept();
				if(peek() == '<') {
					t.name = Shift_Operator;
					accept();
					t.sot = Left;
				}
				else {
					t.name = Relational_Operator;
					t.rot = Less_Than;
					if(peek() == '=') {
						accept();
						t.rot = Less_Than_Or_Equal;
					}
				}
				break;
			case('>'):
				accept();
				if(peek() == '>') {
					t.name = Shift_Operator;
					accept();
					t.sot = Right;
				}
				else {
					t.name = Relational_Operator;
					t.rot = Greater_Than;
					if(peek() == '=') {
						t.rot = Greater_Than_Or_Equal;
						accept();
					}
				}
				break;
			case('+'):
				t.name = Arithmetic_Operator;
				t.aot = Add;
				accept();
				break;
			case('-'):
				t.name = Arithmetic_Operator;
				t.aot = Subtract;
				accept();
				break;
			case('*'):
				t.name = Arithmetic_Operator;
				t.aot = Multiply;
				accept();
				break;
			case('/'):
				t.name = Arithmetic_Operator;
				t.aot = Divide;
				accept();
				break;
			case('%'):
				t.name = Arithmetic_Operator;
				t.aot = Modulo;
				accept();
				break;
			case('&'):
				t.name = Bitwise_Operator;
				t.bot = Bitwise_And;
				accept();
				break;
			case('|'):
				t.name = Bitwise_Operator;
				t.bot = Bitwise_Or;
				accept();
				break;
			case('^'):
				t.name = Bitwise_Operator;
				t.bot = Bitwise_XOr;
				accept();
				break;
			case('~'):
				t.name = Bitwise_Operator;
				t.bot = Bitwise_Complement;
				accept();
				break;
			case('?'):
				t.name = Conditional_Operator;
				accept();
				break;				
			default:
				std::stringstream ss;
				ss << "invalid character, no token was lexed";
				throw std::runtime_error(ss.str());
				break;
		}
	}
	return t;
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
		case Left_Brace:
			std::cout << "<left-brace>" << "\n";
			break;
		case Right_Brace:
			std::cout << "<right-brace>" << "\n";
			break;
		case Left_Paren:
			std::cout << "<left-paren>" << "\n";
			break;
		case Right_Paren:
			std::cout << "<right-paren>" << "\n";
			break;
		case Left_Bracket:
			std::cout << "<left-bracket>" << "\n";
			break;
		case Right_Bracket:
			std::cout << "<right-bracket>" << "\n";
			break;
		case Comma:
			std::cout << "<comma>" << "\n";
			break;
		case Semicolon:
			std::cout << "<semicolon>" << "\n";
			break;
		case Colon:
			std::cout << "<colon>" << "\n";
			break;
		case Relational_Operator:
			std::cout << "<relational-operator "; 
			switch(t.rot) {
				case(Equal):
					std::cout << "equal";
					break;
				case(Not_Equal):
					std::cout << "not-equal";
					break;
				case(Less_Than):
					std::cout << "less-than";
					break;
				case(Greater_Than):
					std::cout << "greater-than";
					break;
				case(Less_Than_Or_Equal):
					std::cout << "less-than-or-equal";
					break;
				case(Greater_Than_Or_Equal):
					std::cout << "greater-than-or-equal";
					break;
			}
			std::cout << ">\n";
			break;
		case Arithmetic_Operator:
			std::cout << "<arithmetic-operator "; 
			switch(t.aot) {
				case(Add):
					std::cout << "add";
					break;
				case(Subtract):
					std::cout << "subtract";
					break;
				case(Multiply):
					std::cout << "multiply";
					break;
				case(Divide):
					std::cout << "divide";
					break;
				case(Modulo):
					std::cout << "modulo";
					break;
			}
			std::cout << ">\n";
			break;
		case Bitwise_Operator:
			std::cout << "<bitwise-operator "; 
			switch(t.bot) {
				case(Bitwise_And):
					std::cout << "bitwise-and";
					break;
				case(Bitwise_Or):
					std::cout << "bitwise-or";
					break;
				case(Bitwise_XOr):
					std::cout << "bitwise-xor";
					break;
				case(Bitwise_Complement):
					std::cout << "bitwise-complement";
					break;
			}
			std::cout << ">\n";
			break;
		case Logical_Operator:
			std::cout << "<logical-operator: "; 
			switch(t.lot) {
				case(And):
					std::cout << "and";
					break;
				case(Or):
					std::cout << "or";
					break;
				case(Not):
					std::cout << "not";
					break;
			}
			std::cout << ">\n";
			break;
		case Conditional_Operator:
			std::cout << "<conditional-operator>" << "\n";
			break;
		case Assignment_Operator:
			std::cout << "<assignment-operator>" << "\n";
			break;
		case Keyword_Bool:
			std::cout << "<bool>" << "\n";
			break;
		case Keyword_Char:
			std::cout << "<char>" << "\n";
			break;
		case Keyword_Def:
			std::cout << "<def>" << "\n";
			break;
		case Keyword_Else:
			std::cout << "<else>" << "\n";
			break;
		case Keyword_False:
			std::cout << "<false>" << "\n";
			break;
		case Keyword_Float:
			std::cout << "<float>" << "\n";
			break;
		case Keyword_If:
			std::cout << "<if>" << "\n";
			break;
		case Keyword_Int:
			std::cout << "<int>" << "\n";
			break;
		case Keyword_Let:
			std::cout << "<let>" << "\n";
			break;
		case Keyword_True:
			std::cout << "<true>" << "\n";
			break;
		case Keyword_Var:
			std::cout << "<var>" << "\n";
			break;
		case Identifier:
			std::cout << "<identifier: " << symbols.matchSymbol(t.symbolTableIndex) << ">\n";
			break;
		case Decimal_Integer_Literal:
			std::cout << "<decimal-integer-literal " << t.integerValue << ">\n";
			break;
		case Hexadecimal_Integer_Literal:
			std::cout << "<hexadecimal-integer-literal: 0x" << std::hex << t.integerValue << ">\n";
			break;
		case Binary_Integer_Literal:
			std::cout << "<binary-integer-literal: 0b"; printAsBinary(t.integerValue); std::cout << ">\n";
			break;
		case Floating_Point_Literal:
			std::cout << "<floating-point-literal: " << t.floatValue << ">\n";
			break;
		case Boolean_Literal:
			std::cout << "<boolean-literal: "; 
			switch(t.blt) {
				case(True):
					std::cout << "true";
					break;
				case(False):
					std::cout << "false";
					break;
			}
			std::cout << ">\n";
			break;
		case Character_Literal:
			std::cout << "<character-literal: '"; 
			switch(t.charVal) {
				case('\''):
					std::cout << "\\'";
					break;
				case('\"'):
					std::cout << "\\\"";
					break;
				case('\\'):
					std::cout << "\\\\";
					break;
				case('\a'):
					std::cout << "\\a";
					break;
				case('\b'):
					std::cout << "\\b";
					break;
				case('\f'):
					std::cout << "\\f";
					break;
				case('\n'):
					std::cout << "\\n";
					break;
				case('\r'):
					std::cout << "\\r";
					break;
				case('\t'):
					std::cout << "\\t";
					break;
				case('\v'):
					std::cout << "\\v";
					break;
				default:
					std::cout << t.charVal;
					break;
			}
			std::cout << "'>\n";
			break;
		case String_Literal:
			std::cout << "<string-literal: \"" << symbols.matchSymbol(t.symbolTableIndex) << "\">\n";
			break;
	}
}

void Lexer::printAsBinary(int val) {
	std::string s = "";
	while(val > 0) {
		s = std::to_string(val % 2) + s;
		val = val/2;
	}
	std::cout << s;
}