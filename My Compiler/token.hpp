//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum TokenName {
	Left_Brace,
	Right_Brace,
	Left_Paren,
	Right_Paren,
	Left_Bracket,
	Right_Bracket,
	Comma,
	Semicolon,
	Colon,
	Relational_Operator,
	Arithmetic_Operator,
	Bitwise_Operator,
	Logical_Operator,
	Conditional_Operator,
	Assignment_Operator,
	Shift_Operator,
	Keyword_And,
	Keyword_As,
	Keyword_Bool,
	Keyword_Break,
	Keyword_Char,
	Keyword_Const,
	Keyword_Continue,
	Keyword_Def,
	Keyword_Else,
	Keyword_False,
	Keyword_Float,
	Keyword_If,
	Keyword_Int,
	Keyword_Let,
	Keyword_Not,
	Keyword_Or,
	Keyword_Return,
	Keyword_True,
	Keyword_Var,
	Keyword_Void,
	Keyword_Volatile,
	Keyword_While,
	Identifier,
	Decimal_Integer_Literal,
	Hexadecimal_Integer_Literal,
	Binary_Integer_Literal,
	Floating_Point_Literal,
	Boolean_Literal,
	Character_Literal,
	String_Literal
};

enum RelationalOperatorType {
	Equal,
	Not_Equal,
	Less_Than,
	Greater_Than,
	Less_Than_Or_Equal,
	Greater_Than_Or_Equal
};

enum ArithmeticOperatorType {
	Add,
	Subtract,
	Multiply,
	Divide,
	Modulo
};

enum BitwiseOperatorType {
	Bitwise_And,
	Bitwise_Or,
	Bitwise_XOr,
	Bitwise_Complement
};

enum LogicalOperatorType {
	And,
	Or,
	Not
};

enum ShiftOperatorType {
	Left,
	Right
};

enum BooleanLiteralType {
	True,
	False
};

class Token {	
	public:
		TokenName name;
		int location;
		
		union {
			char charVal;		
			int integerValue;
			double floatValue;
			int symbolTableIndex;
			RelationalOperatorType rot;
			ArithmeticOperatorType aot;
			BitwiseOperatorType bot;
			LogicalOperatorType lot;
			BooleanLiteralType blt;
			ShiftOperatorType sot;
		};
		
	private:
		
};


#endif