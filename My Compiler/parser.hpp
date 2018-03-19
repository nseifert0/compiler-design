//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

#include <deque>

class Parser {
	public:
		Parser(const char* filepath): lexer(filepath) {
		}
		
		void parse();
		
		//Parsing Types
		void parseBasicType();
		void parseTypeList();
		void parsePostfixType();
		void parseReferenceType();
		void parseType();
		
		//Parsing Expressions
		void parsePrimaryExpression();
		void parsePostfixExpression();
		void parseArgumentList();
		void parseArgument();
		void parseUnaryExpression();
		void parseCastExpression();
		void parseMultiplicativeExpression();
		void parseAdditiveExpression();
		void parseShiftExpression();
		void parseRelationalExpression();
		void parseEqualityExpression();
		void parseBitwiseAndExpression();
		void parseBitwiseXorExpression();
		void parseBitwiseOrExpression();
		void parseLogicalAndExpression();
		void parseLogicalOrExpression();
		void parseConditionalExpression();
		void parseAssignmentExpression();
		void parseExpression();
		void parseConstantExpression();
	
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
};

#endif