#include "token.hpp"
#include <iostream>

void Token::print() {
	switch(name) {
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
		case Identifier:std::cout << "<identifier: " << identifierIndex << ">\n";
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
		case Character_Literal: std::cout << "<character-literal>" << "\n";
			break;
		case String_Literal: std::cout << "<string-literal>" << "\n";
			break;
	}
}