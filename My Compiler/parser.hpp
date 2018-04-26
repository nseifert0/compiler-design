//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "decl.hpp"

#include <deque>

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
		void parseStatement();
		void parseBlockStatement();
		void parseStatementSeq();
		void parseIfStatement();
		void parseWhileStatement();
		void parseBreakStatement();
		void parseContinueStatement();
		void parseReturnStatement();
		void parseDeclarationStatement();
		void parseExpressionStatement();
		
		//Parsing Declarations
		void parseProgram();
		void parseDeclarationSeq();
		void parseDeclaration();
		void parseLocalDeclaration();
		void parseObjectDefinition();
		void parseVariableDefinition();
		void parseConstantDefinition();
		void parseValueDefinition();
		void parseFunctionDefinition();
		void parseParameterList();
		void parseParameter();
	
	private:
		Lexer lexer;
		std::deque<Token> tokenQueue;
		
		//Parser Utilities
		void pushToken();
		Token lookAhead(int howMuch);
		Token accept();
		Token acceptSpecific(TokenName tokenName);
		bool checkIfPostfixType();
		bool checkIfUnaryExpression();
		bool checkIfMultiplicativeExpression();
		bool checkIfAdditiveExpression();
		bool checkIfRelationalExpression();
		bool checkIfEqualityExpression();
};

#endif