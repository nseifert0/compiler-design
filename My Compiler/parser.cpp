//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"

void Parser::parse() {
}

//------------------------------------------------------------------------------
//Parsing Types
void Parser::parseBasicType() {
}

void Parser::parseTypeList() {
}

void Parser::parsePostfixType() {
}

void Parser::parseReferenceType() {
}

void Parser::parseType() {
}

//------------------------------------------------------------------------------
//Parsing Expressions
void Parser::parsePrimaryExpression() {
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