//Nicholas Seifert
//Compiler Design - Spring 2018
//TODO: Implement arrow operator and fix sections with arrow operator
//		Add a print function for the token names, this will allow for errors to show expected token 

#include "parser.hpp"

#include <sstream>

void Parser::parse() {
	parseProgram();
}

//------------------------------------------------------------------------------
//Parsing Types
Type* Parser::parseBasicType() {
	switch(lookAhead(0).name) {
		case Keyword_Void:
		case Keyword_Bool:
		case Keyword_Int:
		case Keyword_Float:
		case Keyword_Char:
			accept();
			return new Type(typeIsTest);
		
		
		//Not sure what to do here based upon the language description, is there an -> operator?
		case Left_Paren:
			accept();
			if(lookAhead(0).name != Right_Paren) {
				parseTypeList();
			}
			acceptSpecific(Right_Paren);
			return new Type(typeIsTest);
		
		default:
			std::stringstream ss;
			ss << "Syntax Error";
			throw std::runtime_error(ss.str());
	}
}

Type* Parser::parseTypeList() {
	parseType();
	while(lookAhead(0).name == Comma) {
		accept();
		parseType();
	}
	return new Type(typeIsTest);
}

Type* Parser::parsePostfixType() {
	parseBasicType();
	while(checkIfPostfixType()) {
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
	return new Type(typeIsTest);
}

Type* Parser::parseReferenceType() {
	parsePostfixType();
	while(lookAhead(0).name == Bitwise_Operator) {
		if(lookAhead(0).bot == Bitwise_And) {
			accept();
		}
		else {
			break;
		}
	}
	return new Type(typeIsTest);
}

Type* Parser::parseType() {
	parsePostfixType();
	return new Type(typeIsTest);
}

//------------------------------------------------------------------------------
//Parsing Expressions
Expr* Parser::parsePrimaryExpression() {
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
			return new Expr(exprIsTest);
		
		case Left_Paren:
			accept();
			parseExpression();
			acceptSpecific(Right_Paren);
		
		default:
			std::stringstream ss;
			ss << "Syntax Error";
			throw std::runtime_error(ss.str());
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parsePostfixExpression() {
	parsePrimaryExpression();
	switch(lookAhead(0).name) {
		case Left_Paren:
			accept();
			if(lookAhead(0).name != Right_Paren) {
				parseArgumentList();
			}
			acceptSpecific(Right_Paren);
			break;
		case Left_Bracket:
			accept();
			if(lookAhead(0).name != Right_Bracket) {
				parseArgumentList();
			}
			acceptSpecific(Right_Bracket);
			break;
		default:
			break;
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseArgumentList() {
	parseArgument();
	while(lookAhead(0).name == Comma) {
		accept();
		parseArgument();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseArgument() {
	parseExpression();
	return new Expr(exprIsTest);
}

Expr* Parser::parseUnaryExpression() {
	while(checkIfUnaryExpression()) {
		accept();
	}
	parsePostfixExpression();
	return new Expr(exprIsTest);
}

Expr* Parser::parseCastExpression() {
	parseUnaryExpression();
	while(lookAhead(0).name == Keyword_As) {
		accept();
		parseType();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseMultiplicativeExpression() {
	parseCastExpression();
	while(checkIfMultiplicativeExpression()) {
		accept();
		parseCastExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseAdditiveExpression() {
	parseMultiplicativeExpression();
	while(checkIfAdditiveExpression()) {
		accept();
		parseMultiplicativeExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseShiftExpression() {
	parseAdditiveExpression();
	while(lookAhead(0).name == Shift_Operator) {
		accept();
		parseAdditiveExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseRelationalExpression() {
	parseShiftExpression();
	while(checkIfRelationalExpression()) {
		accept();
		parseShiftExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseEqualityExpression() {
	parseRelationalExpression();
	while(checkIfEqualityExpression()) {
		accept();
		parseRelationalExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseBitwiseAndExpression() {
	parseEqualityExpression();
	while(lookAhead(0).name == Bitwise_Operator) {
		if(lookAhead(0).bot == Bitwise_And) {
			accept();
			parseEqualityExpression();
		}
		else {
			break;
		}
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseBitwiseXorExpression() {
	parseBitwiseAndExpression();
	while(lookAhead(0).name == Bitwise_Operator) {
		if(lookAhead(0).bot == Bitwise_XOr) {
			accept();
			parseBitwiseAndExpression();
		}
		else {
			break;
		}
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseBitwiseOrExpression() {
	parseBitwiseXorExpression();
	while(lookAhead(0).name == Bitwise_Operator) {
		if(lookAhead(0).bot == Bitwise_Or) {
			accept();
			parseBitwiseXorExpression();
		}
		else {
			break;
		}
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseLogicalAndExpression() {
	parseBitwiseOrExpression();
	while(lookAhead(0).name == Logical_Operator) {
		if(lookAhead(0).lot == And) {
			accept();
			parseBitwiseOrExpression();
		}
		else {
			break;
		}
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseLogicalOrExpression() {
	parseLogicalAndExpression();
	while(lookAhead(0).name == Logical_Operator) {
		if(lookAhead(0).lot == Or) {
			accept();
			parseLogicalAndExpression();
		}
		else {
			break;
		}
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseConditionalExpression() {
	parseLogicalOrExpression();
	if(lookAhead(0).name == Conditional_Operator) {
		accept();
		parseExpression();
		acceptSpecific(Colon);
		parseConditionalExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseAssignmentExpression() {
	parseConditionalExpression();
	while(lookAhead(0).name == Assignment_Operator) {
		accept();
		parseConditionalExpression();
	}
	return new Expr(exprIsTest);
}

Expr* Parser::parseExpression() {
	parseAssignmentExpression();
	return new Expr(exprIsTest);
}

Expr* Parser::parseConstantExpression() {
	parseConditionalExpression();
	return new Expr(exprIsTest);
}


//------------------------------------------------------------------------------
//Parsing Statements
void Parser::parseStatement() {
	switch(lookAhead(0).name) {
		case Right_Bracket:
			parseBlockStatement();
			break;
		case Keyword_If:
			parseIfStatement();
			break;
		case Keyword_While:
			parseWhileStatement();
			break;
		case Keyword_Continue:
			parseContinueStatement();
			break;
		case Keyword_Return:
			parseReturnStatement();
			break;
		case Keyword_Var:
		case Keyword_Let:
		case Keyword_Def:
			parseDeclarationStatement();
			break;
		default:
			parseExpressionStatement();
			break;
	}
}

void Parser::parseBlockStatement() {
	acceptSpecific(Left_Bracket);
	if(lookAhead(0).name != Right_Bracket) {
		parseStatementSeq();
	}
	acceptSpecific(Right_Bracket);
}

void Parser::parseStatementSeq() {
	//Statement Sequences Only Appear in Block Statements
	//Block Statements are Surrounded by Brackets.
	parseStatement();
	while(lookAhead(0).name != Right_Bracket) {
		parseStatement();
	}
}

void Parser::parseIfStatement() {
	acceptSpecific(Keyword_If);
	acceptSpecific(Left_Paren);
	parseExpression();
	acceptSpecific(Right_Paren);
	parseStatement();
	if(lookAhead(0).name == Keyword_Else) {
		accept();
		parseStatement();
	}
}

void Parser::parseWhileStatement() {
	acceptSpecific(Keyword_While);
	acceptSpecific(Left_Paren);
	parseExpression();
	acceptSpecific(Right_Paren);
	parseStatement();
}

void Parser::parseBreakStatement() {
	acceptSpecific(Keyword_Break);
	acceptSpecific(Semicolon);
}

void Parser::parseContinueStatement() {
	acceptSpecific(Keyword_Continue);
	acceptSpecific(Semicolon);
}

void Parser::parseReturnStatement() {
	acceptSpecific(Keyword_Return);
	if(lookAhead(0).name != Semicolon) {
		parseExpression();
	}
	acceptSpecific(Semicolon);
}

void Parser::parseDeclarationStatement() {
	parseLocalDeclaration();
}

void Parser::parseExpressionStatement() {
	parseExpression();
	acceptSpecific(Semicolon);
}

//------------------------------------------------------------------------------
//Parsing Declarations
void Parser::parseProgram() {
	if(!lexer.eof()) {
		parseDeclarationSeq();
	}
}

void Parser::parseDeclarationSeq() {
	parseDeclaration();
	while(!lexer.eof()) {
		parseDeclaration();
	}
}

void Parser::parseDeclaration() {
	switch(lookAhead(2).name) {
		case Left_Paren:
			parseFunctionDefinition();
			break;
		case Colon:
			parseObjectDefinition();
			break;
	}
}

void Parser::parseLocalDeclaration() {
	parseObjectDefinition();
}

void Parser::parseObjectDefinition() {
	switch(lookAhead(0).name) {
		case Keyword_Var:
			parseVariableDefinition();
			break;
		case Keyword_Let:
			parseConstantDefinition();
			break;
		case Keyword_Def:
			parseValueDefinition();
			break;
	}
}

void Parser::parseVariableDefinition() {
	acceptSpecific(Keyword_Var);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	switch(lookAhead(0).name) {
		case Semicolon:
			accept();
			break;
		case Assignment_Operator:
			accept();
			parseExpression();
			acceptSpecific(Semicolon);
			break;
	}
}

void Parser::parseConstantDefinition() {
	acceptSpecific(Keyword_Let);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	acceptSpecific(Assignment_Operator);
	parseExpression();
	acceptSpecific(Semicolon);
}

void Parser::parseValueDefinition() {
	acceptSpecific(Keyword_Def);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	acceptSpecific(Assignment_Operator);
	parseExpression();
	acceptSpecific(Semicolon);
}

void Parser::parseFunctionDefinition() {
	acceptSpecific(Keyword_Def);
	acceptSpecific(Identifier);
	acceptSpecific(Left_Paren);
	if(lookAhead(0).name != Right_Paren) {
		parseParameterList();
	}
	acceptSpecific(Right_Paren);
	//TODO IMPLEMENT ARROW OPERATOR
	//acceptSpecific(Arrow_Operator);
	parseType();
	parseBlockStatement();
	
}

void Parser::parseParameterList() {
	parseParameter();
	while(lookAhead(0).name != Right_Paren) {
		parseParameter();
	}
}

void Parser::parseParameter() {
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
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

bool Parser::checkIfPostfixType() {
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

// Specfics of the language are again kind of unclear here, especially since "!" isn't in the language
bool Parser::checkIfUnaryExpression() {
	switch(lookAhead(0).name) {
		case Arithmetic_Operator:
			switch(lookAhead(0).aot) {
				case Add:
				case Subtract:
				case Multiply:
					return true;
				default:
					return false;
			}
		case Bitwise_Operator:
			switch(lookAhead(0).bot) {
				case Bitwise_And:
				case Bitwise_Complement:
					return true;
				default:
					return false;
			}
		case Logical_Operator:
			switch(lookAhead(0).lot) {
				case Not:
					return true;
				default:
					return false;
			}
		default:
			return false;
	}	
}

bool Parser::checkIfMultiplicativeExpression() {
	if(lookAhead(0).name == Arithmetic_Operator)
		switch(lookAhead(0).aot) {
			case Multiply:
			case Divide:
			case Modulo:
				return true;
			default:
				return false;
		}
	else {
		return false;
	}
}

bool Parser::checkIfAdditiveExpression() {
	if(lookAhead(0).name == Arithmetic_Operator)
		switch(lookAhead(0).aot) {
			case Add:
			case Subtract:
				return true;
			default:
				return false;
		}
	else {
		return false;
	}
}

bool Parser::checkIfRelationalExpression() {
	if(lookAhead(0).name == Relational_Operator)
		switch(lookAhead(0).rot) {
			case Less_Than:
			case Less_Than_Or_Equal:
			case Greater_Than:
			case Greater_Than_Or_Equal:
				return true;
			default:
				return false;
		}
	else {
		return false;
	}
}

bool Parser::checkIfEqualityExpression() {
	if(lookAhead(0).name == Relational_Operator)
		switch(lookAhead(0).rot) {
			case Equal:
			case Not_Equal:
				return true;
			default:
				return false;
		}
	else {
		return false;
	}
}