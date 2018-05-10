//Nicholas Seifert
//Compiler Design - Spring 2018

#include "parser.hpp"

#include <sstream>
#include <string>

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
			return semantics.basicType(accept());
		case Left_Paren:
			accept();
			if(lookAhead(0).name != Right_Paren) {
				parseTypeList();
			}
			acceptSpecific(Right_Paren);
			return new Type(typeIsTest);
		
		default:
			std::stringstream ss;
			ss << "Syntax Error in Parsing a basic type";
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
	return parseBasicType();
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
	return parsePostfixType();
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
			ss << "Syntax Error in Parsing Primary Expression";
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
	return new Expr(exprIsTest);
	//return parseAssignmentExpression();
}

Expr* Parser::parseConstantExpression() {
	parseConditionalExpression();
	return new Expr(exprIsTest);
}


//------------------------------------------------------------------------------
//Parsing Statements
Stmt* Parser::parseStatement() {
	switch(lookAhead(0).name) {
		case Right_Bracket:
			return parseBlockStatement();
			break;
		case Keyword_If:
			return parseIfStatement();
			break;
		case Keyword_While:
			return parseWhileStatement();
			break;
		case Keyword_Continue:
			return parseContinueStatement();
			break;
		case Keyword_Return:
			return parseReturnStatement();
			break;
		case Keyword_Var:
		case Keyword_Let:
		case Keyword_Def:
			return parseDeclarationStatement();
			break;
		default:
			return parseExpressionStatement();
			break;
	}
}

Stmt* Parser::parseBlockStatement() {
	acceptSpecific(Left_Brace);
	StmtSequence sS;
	if(lookAhead(0).name != Right_Brace) {
		sS = parseStatementSeq();
	}
	acceptSpecific(Right_Brace);
	return new BlockStmt(sS);
}

StmtSequence Parser::parseStatementSeq() {
	//Statement Sequences Only Appear in Block Statements
	//Block Statements are Surrounded by Brackets.
	StmtSequence sS;
	sS.push_back(parseStatement());
	while(lookAhead(0).name != Right_Bracket) {
		sS.push_back(parseStatement());
	}
	return sS;
}

Stmt* Parser::parseIfStatement() {
	acceptSpecific(Keyword_If);
	acceptSpecific(Left_Paren);
	Expr* cond = parseExpression();
	acceptSpecific(Right_Paren);
	Stmt* res = parseStatement();
	if(lookAhead(0).name == Keyword_Else) {
		accept();
		parseStatement();
	}
	return new IfStmt(cond, res);
}

Stmt* Parser::parseWhileStatement() {
	acceptSpecific(Keyword_While);
	acceptSpecific(Left_Paren);
	parseExpression();
	acceptSpecific(Right_Paren);
	parseStatement();
	return new Stmt(stmtIsTest);
}

Stmt* Parser::parseBreakStatement() {
	acceptSpecific(Keyword_Break);
	acceptSpecific(Semicolon);
	return new Stmt(stmtIsTest);
}

Stmt* Parser::parseContinueStatement() {
	acceptSpecific(Keyword_Continue);
	acceptSpecific(Semicolon);
	return new Stmt(stmtIsTest);
}

Stmt* Parser::parseReturnStatement() {
	acceptSpecific(Keyword_Return);
	if(lookAhead(0).name != Semicolon) {
		parseExpression();
	}
	acceptSpecific(Semicolon);
	return new Stmt(stmtIsTest);
}

Stmt* Parser::parseDeclarationStatement() {
	parseLocalDeclaration();
	return new Stmt(stmtIsTest);
}

Stmt* Parser::parseExpressionStatement() {
	parseExpression();
	acceptSpecific(Semicolon);
	return new Stmt(stmtIsTest);
}

//------------------------------------------------------------------------------
//Parsing Declarations
Decl* Parser::parseProgram() {
	if(!lexer.eof()) {
		DeclList sequence = parseDeclarationSeq();
		return new ProgramDecl(sequence);
	}
	else {
		return nullptr;
	}
}

DeclList Parser::parseDeclarationSeq() {
	DeclList dL;
	dL.push_back(parseDeclaration());
	while(!lexer.eof()) {
		dL.push_back(parseDeclaration());
	}
	return dL;
}

Decl* Parser::parseDeclaration() {
	switch(lookAhead(2).name) {
		case Left_Paren:
			return parseFunctionDefinition();
			break;
		case Colon:
			return parseObjectDefinition();
			break;
		default:
			std::stringstream ss;
			ss << "Expected a function or object definition";
			throw std::runtime_error(ss.str());
	}
}

Decl* Parser::parseLocalDeclaration() {
	return parseObjectDefinition();
}

Decl* Parser::parseObjectDefinition() {
	switch(lookAhead(0).name) {
		case Keyword_Var:
			return parseVariableDefinition();
			break;
		case Keyword_Let:
			return parseConstantDefinition();
			break;
		case Keyword_Def:
			return parseValueDefinition();
			break;
		default:
			std::stringstream ss;
			ss << "Expected an object definition";
			throw std::runtime_error(ss.str());
	}
}

Decl* Parser::parseVariableDefinition() {
	acceptSpecific(Keyword_Var);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	Type* t = parseType();
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
	return new VariableDefinitionDecl(nullptr, t, nullptr);
}

Decl* Parser::parseConstantDefinition() {
	acceptSpecific(Keyword_Let);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	acceptSpecific(Assignment_Operator);
	parseExpression();
	acceptSpecific(Semicolon);
	return new Decl(declIsTest);
}

Decl* Parser::parseValueDefinition() {
	acceptSpecific(Keyword_Def);
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	acceptSpecific(Assignment_Operator);
	parseExpression();
	acceptSpecific(Semicolon);
	return new Decl(declIsTest);
}

Decl* Parser::parseFunctionDefinition() {
	acceptSpecific(Keyword_Def);
	acceptSpecific(Identifier);
	acceptSpecific(Left_Paren);
	DeclList dL;
	if(lookAhead(0).name != Right_Paren) {
		//DeclList dL = parseParameterList();
	}
	acceptSpecific(Right_Paren);
	//acceptSpecific(Arrow_Operator);
	Type* t = parseType();
	Stmt* s = parseBlockStatement();
	return new FunctionDefinitionDecl(new Symbol, dL, t, s);
	
}

Decl* Parser::parseParameterList() {
	parseParameter();
	while(lookAhead(0).name != Right_Paren) {
		parseParameter();
	}
}

Decl* Parser::parseParameter() {
	acceptSpecific(Identifier);
	acceptSpecific(Colon);
	parseType();
	return new Decl(declIsTest);
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
		ss << "Syntax Error expected a" << getTokenNameAsString(tokenName);
		throw std::runtime_error(ss.str());
	}
}

std::string Parser::getTokenNameAsString(TokenName tN) {
	switch(tN) {
		case Left_Brace:
			return "{";
		case Right_Brace:
			return "}";
		case Left_Paren:
			return "(";
		case Right_Paren:
			return ")";
		case Left_Bracket:
			return "[";
		case Right_Bracket:
			return "]";
		case Comma:
			return ",";
		case Semicolon:
			return ":";
		case Colon:
			return ";";
		case Relational_Operator:
			return "Relational_Operator";
		case Arithmetic_Operator:
			return "Arithmetic_Operator";
		case Bitwise_Operator:
			return "Bitwise_Operator";
		case Logical_Operator:
			return "";
		case Conditional_Operator:
			return "";
		case Assignment_Operator:
			return "";
		case Shift_Operator:
			return "";
		case Keyword_And:
			return "And";
		case Keyword_As:
			return "As";
		case Keyword_Bool:
			return "Bool";
		case Keyword_Break:
			return "Break";
		case Keyword_Char:
			return "Char";
		case Keyword_Const:
			return "Const";
		case Keyword_Continue:
			return "Continue";
		case Keyword_Def:
			return "";
		case Keyword_Else:
			return "";
		case Keyword_False:
			return "";
		case Keyword_Float:
			return "";
		case Keyword_If:
			return "";
		case Keyword_Int:
			return "";
		case Keyword_Let:
			return "";
		case Keyword_Not:
			return "";
		case Keyword_Or:
			return "";
		case Keyword_Return:
			return "";
		case Keyword_True:	
			return "";
		case Keyword_Var:
			return "";
		case Keyword_Void:
			return "";
		case Keyword_Volatile:
			return "";
		case Keyword_While:
			return "";
		case Identifier:
			return "";
		case Decimal_Integer_Literal:
			return "";
		case Hexadecimal_Integer_Literal:
			return "";
		case Binary_Integer_Literal:
			return "";
		case Floating_Point_Literal:
			return "";
		case Boolean_Literal:
			return "";
		case Character_Literal:
			return "";
		case String_Literal:
			return "";
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