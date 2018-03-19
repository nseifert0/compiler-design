//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"

#include <sstream>

void Parser::parse() {
}

//------------------------------------------------------------------------------
//Parsing Types
void Parser::parseBasicType() {
	switch(lookAhead(0).name) {
		case Keyword_Void:
		case Keyword_Bool:
		case Keyword_Int:
		case Keyword_Float:
		case Keyword_Char:
			accept();
			return;
		
		
		//Not sure what to do here based upon the language description, is there an -> operator?
		case Left_Paren:
			accept();
			if(lookAhead(0).name != Right_Paren) {
				parseTypeList();
			}
			acceptSpecific(Right_Paren);
			return;
		
		default:
			std::stringstream ss;
			ss << "Syntax Error";
			throw std::runtime_error(ss.str());
	}
}

void Parser::parseTypeList() {
	parseType();
	while(lookAhead(0).name == Comma) {
		accept();
		parseType();
	}
}

void Parser::parsePostfixType() {
	parseBasicType();
	while(checkIfPostfix()) {
		if(lookAhead(0).name == Left_Bracket) {
			accept();
			if(lookAhead(0).name == Right_Bracket) {
				accept();
			}
			else {
				parseExpression();
				acceptSpecific(Right_Bracket);
			}
		}
		else {
			accept();
		}
	}
}

void Parser::parseReferenceType() {
	parsePostfixType();
	while(lookAhead(0).name == Bitwise_Operator) {
		if(lookAhead(0).bot == Bitwise_And) {
			accept();
		}
		else {
			break;
		}
	}
}

void Parser::parseType() {
	parsePostfixType();
}

//------------------------------------------------------------------------------
//Parsing Expressions
void Parser::parsePrimaryExpression() {
	switch(lookAhead(0).name) {
		case Decimal_Integer_Literal:
		case Hexadecimal_Integer_Literal:
		case Binary_Integer_Literal:
		case Floating_Point_Literal:
		case Boolean_Literal:
		case Character_Literal:
		case String_Literal:
		case Identifier:
			accept();
			return;
		
		case Left_Paren:
			accept();
			parseExpression();
			acceptSpecific(Right_Paren);
		
		default:
			std::stringstream ss;
			ss << "Syntax Error";
			throw std::runtime_error(ss.str());
	}
	
}

void Parser::parsePostfixExpression() {
}

void Parser::parseArgumentList() {
}

void Parser::parseArgument() {
}

void Parser::parseUnaryExpression() {
}

void Parser::parseCastExpression() {
}

void Parser::parseMultiplicativeExpression() {
}

void Parser::parseAdditiveExpression() {
}

void Parser::parseShiftExpression() {
}

void Parser::parseRelationalExpression() {
}

void Parser::parseEqualityExpression() {
}

void Parser::parseBitwiseAndExpression() {
}

void Parser::parseBitwiseXorExpression() {
}

void Parser::parseBitwiseOrExpression() {
}

void Parser::parseLogicalAndExpression() {
}

void Parser::parseLogicalOrExpression() {
}

void Parser::parseConditionalExpression() {
}

void Parser::parseAssignmentExpression() {
}

void Parser::parseExpression() {
}

void Parser::parseConstantExpression() {
}


//------------------------------------------------------------------------------
//Parsing Statements
void Parser::parseStatement() {
}

void Parser::parseBlockStatement() {
}

void Parser::parseStatementSeq() {
}

void Parser::parseIfStatement() {
}

void Parser::parseWhileStatement() {
}

void Parser::parseBreakStatement() {
}

void Parser::parseContinueStatement() {
}

void Parser::parseReturnStatement() {
}

void Parser::parseDeclarationStatement() {
}

void Parser::parseExpressionStatement() {
}

//------------------------------------------------------------------------------
//Parsing Declarations
void Parser::parseProgram() {
}

void Parser::parseDeclarationSeq() {
}

void Parser::parseDeclaration() {
}

void Parser::parseLocalDeclaration() {
}

void Parser::parseObjectDefinition() {
}

void Parser::parseVariableDefinition() {
}

void Parser::parseConstantDefinition() {
}

void Parser::parseValueDefinition() {
}

void Parser::parseFunctionDefinition() {
}

void Parser::parseParameterList() {
}

void Parser::parseParameter() {
}

//------------------------------------------------------------------------------
//Parser Utilities
void Parser::pushToken() {
	tokenQueue.push_back(lexer.lex());
}

Token Parser::lookAhead(int howMuch) {
	while(tokenQueue.size() < howMuch + 1) {
		pushToken();
	}
	return tokenQueue[howMuch];
}

Token Parser::accept() {
	Token acceptedToken = lookAhead(0);
	tokenQueue.pop_front();
	return acceptedToken;
}

Token Parser::acceptSpecific(TokenName tokenName) {
	if(lookAhead(0).name == tokenName) {
		return accept();
	}
	else {
		std::stringstream ss;
		ss << "Syntax Error";
		throw std::runtime_error(ss.str());
	}
}

bool Parser::checkIfPostfix() {
	switch(lookAhead(0).name) {
		case Arithmetic_Operator:
			if(lookAhead(0).aot != Multiply) {
				return false;
			}
		case Keyword_Const:
		case Keyword_Volatile:
		case Keyword_Float:
		case Left_Bracket:
			return true;
		
		default:
			return false;
	}	
}