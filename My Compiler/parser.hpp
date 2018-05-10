//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef PARSER_HPP
#define PARSER_HPP

#include "semantics.hpp"
#include "lexer.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "decl.hpp"

#include <deque>
#include <string>

class Parser {
	public:
		Parser(const char* filepath)
			: lexer(filepath) {
		}
		
		void parse();
		
		//Parsing Types
		Type* parseBasicType();
		Type* parseTypeList();
		Type* parsePostfixType();
		Type* parseReferenceType();
		Type* parseType();
		
		//Parsing Expressions
		Expr* parsePrimaryExpression();
		Expr* parsePostfixExpression();
		Expr* parseArgumentList();
		Expr* parseArgument();
		Expr* parseUnaryExpression();
		Expr* parseCastExpression();
		Expr* parseMultiplicativeExpression();
		Expr* parseAdditiveExpression();
		Expr* parseShiftExpression();
		Expr* parseRelationalExpression();
		Expr* parseEqualityExpression();
		Expr* parseBitwiseAndExpression();
		Expr* parseBitwiseXorExpression();
		Expr* parseBitwiseOrExpression();
		Expr* parseLogicalAndExpression();
		Expr* parseLogicalOrExpression();
		Expr* parseConditionalExpression();
		Expr* parseAssignmentExpression();
		Expr* parseExpression();
		Expr* parseConstantExpression();
	
		//Parsing Statements
		Stmt* parseStatement();
		Stmt* parseBlockStatement();
		StmtSequence parseStatementSeq();
		Stmt* parseIfStatement();
		Stmt* parseWhileStatement();
		Stmt* parseBreakStatement();
		Stmt* parseContinueStatement();
		Stmt* parseReturnStatement();
		Stmt* parseDeclarationStatement();
		Stmt* parseExpressionStatement();
		
		//Parsing Declarations
		Decl* parseProgram();
		DeclList parseDeclarationSeq();
		Decl* parseDeclaration();
		Decl* parseLocalDeclaration();
		Decl* parseObjectDefinition();
		Decl* parseVariableDefinition();
		Decl* parseConstantDefinition();
		Decl* parseValueDefinition();
		Decl* parseFunctionDefinition();
		Decl* parseParameterList();
		Decl* parseParameter();
	
	private:
		Lexer lexer;
		Semantics semantics;
		std::deque<Token> tokenQueue;
		
		//Parser Utilities
		void pushToken();
		Token lookAhead(int howMuch);
		Token accept();
		Token acceptSpecific(TokenName tokenName);
		std::string getTokenNameAsString(TokenName tN);
		bool checkIfPostfixType();
		bool checkIfUnaryExpression();
		bool checkIfMultiplicativeExpression();
		bool checkIfAdditiveExpression();
		bool checkIfRelationalExpression();
		bool checkIfEqualityExpression();
};

#endif