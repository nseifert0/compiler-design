#include "lexer.hpp"
#include <iostream>
#include <bitset>

Token Lexer::lex() {
	Token T;
	lexeme.clear();
	while(isspace(peek())) {
		ignore();
	}
	if(isdigit(peek())) {
		if(peek() == '0') {
			accept();
		}
		switch(peek()) {
			case('x'):
			case('X'):
				T.name = Hexadecimal_Integer_Literal;
				accept();
				while(isxdigit(peek())) {
					lexeme+=accept();
				}
				T.integerValue = std::stoi(lexeme,nullptr,16);
				break;
			case('b'):
			case('B'):
				T.name = Binary_Integer_Literal;
				accept();
				while((peek() == '0') || (peek() == '1')) {
					lexeme+=accept();
				}
				T.integerValue = std::stoi(lexeme,nullptr,2);
				break;
			default:
				while(isdigit(peek())) {
					lexeme+=accept();
				}
				if(peek() == '.') {
					T.name = Floating_Point_Literal;
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
					T.floatValue = std::stod(lexeme);
				}
				else {
					T.name = Decimal_Integer_Literal;
					T.integerValue = std::stoi(lexeme,nullptr,10);
				}
				break;
		}
	}
	else if(isalpha(peek())) {
		while(isalnum(peek()) || peek() == '_') {
			lexeme += accept();
		}
		if(matchKeyword(T)) {
			switch(T.name) {
				case(Keyword_And):
					T.name = Logical_Operator;
					T.lot = And;
					break;
				case(Keyword_Or):
					T.name = Logical_Operator;
					T.lot = Or;
					break;
				case(Keyword_Not):
					T.name = Logical_Operator;
					T.lot = Not;
					break;
				case(Keyword_True):
					T.name = Boolean_Literal;
					T.blt = True;
					break;
				case(Keyword_False):
					T.name = Boolean_Literal;
					T.blt = False;
					break;						
			}
		}
		else {
			T.identifierIndex = symbols.matchSymbol(lexeme);
			T.name = Identifier;
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
				if(peek() == '\\') {
					accept();
					switch(peek()) {
						case('\''):
							T.charVal = '\'';
							break;
						case('\"'):
							T.charVal = '\"';
							break;
						case('\\'):
							T.charVal = '\\';
							break;
						case('a'):
							T.charVal = '\a';
							break;
						case('b'):
							T.charVal = '\b';
							break;
						case('f'):
							T.charVal = '\f';
							break;
						case('n'):
							T.charVal = '\n';
							break;
						case('r'):
							T.charVal = '\r';
							break;
						case('t'):
							T.charVal = '\t';
							break;
						case('v'):
							T.charVal = '\v';
							break;
						default:
							//throw error
							break;
					}
					accept();
				}
				while((peek() != '\'') && (!eof())) {
					T.charVal = accept();
				}
				if(peek() == '\'') {
					accept();
				}
				else{
					//throw error
				}
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
				break;
			case('{'):
				T.name = Left_Brace;
				accept();
				break;
			case('}'):
				T.name = Right_Brace;
				accept();
				break;
			case('('):
				T.name = Left_Paren;
				accept();
				break;
			case(')'):
				T.name = Right_Paren;
				accept();
				break;
			case('['):
				T.name = Left_Bracket;
				accept();
				break;
			case(']'):
				T.name = Right_Bracket;
				accept();
				break;
			case(','):
				T.name = Comma;
				accept();
				break;
			case(';'):
				T.name = Semicolon;
				accept();
				break;					
			case(':'):
				T.name = Colon;
				accept();
				break;
			case('='):
				accept();
				if(peek() == '=')
				{
					accept();
					T.name = Relational_Operator;
					T.rot = Equal;
				}
				else
				{
					T.name = Assignment_Operator;
				}
				break;
			case('!'):
				T.name = Relational_Operator;
				accept();
				if(peek() == '=') {
					accept();
					T.rot = Not_Equal;
				}
				else {
					//Throw error
				}
				break;
			case('<'):
				T.name = Relational_Operator;
				accept();
				T.rot = Less_Than;
				if(peek() == '=') {
					accept();
					T.rot = Less_Than_Or_Equal;
				}
				break;
			case('>'):
				T.name = Relational_Operator;
				accept();
				T.rot = Greater_Than;
				if(peek() == '=') {
					T.rot = Greater_Than_Or_Equal;
					accept();
				}
				break;
			case('+'):
				T.name = Arithmetic_Operator;
				T.aot = Add;
				accept();
				break;
			case('-'):
				T.name = Arithmetic_Operator;
				T.aot = Subtract;
				accept();
				break;
			case('*'):
				T.name = Arithmetic_Operator;
				T.aot = Multiply;
				accept();
				break;
			case('/'):
				T.name = Arithmetic_Operator;
				T.aot = Divide;
				accept();
				break;
			case('%'):
				T.name = Arithmetic_Operator;
				T.aot = Modulo;
				accept();
				break;
			case('&'):
				T.name = Bitwise_Operator;
				T.bot = Bitwise_And;
				accept();
				break;
			case('|'):
				T.name = Bitwise_Operator;
				T.bot = Bitwise_Or;
				accept();
				break;
			case('^'):
				T.name = Bitwise_Operator;
				T.bot = Bitwise_XOr;
				accept();
				break;
			case('~'):
				T.name = Bitwise_Operator;
				T.bot = Bitwise_Complement;
				accept();
				break;
			case('?'):
				T.name = Conditional_Operator;
				accept();
				break;				
			default:
				break;
		}
	}
	return T;
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
			std::cout << "<identifier: " << symbols.matchSymbol(t.identifierIndex) << ">\n";
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
					std::cout << t.charVal << "'>\n";
					break;
			}
			std::cout << "'>\n";
			break;
		case String_Literal:
			std::cout << "<string-literal: \"" << t.strVal << "\">\n";
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