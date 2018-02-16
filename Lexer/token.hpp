#ifndef TOKEN_HPP
#define TOKEN_HPP

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
	Keyword_And,
	Keyword_Bool,
	Keyword_Char,
	Keyword_Def,
	Keyword_Else,
	Keyword_False,
	Keyword_Float,
	Keyword_If,
	Keyword_Int,
	Keyword_Let,
	Keyword_Not,
	Keyword_Or,
	Keyword_True,
	Keyword_Var,
	Identifier,
	Decimal_Integer_Literal,
	Hexadecimal_Integer_Literal,
	Binary_Integer_Literal,
	Floating_Point_Literal,
	Boolean_Literal,
	Character_Literal,
	String_Literal
};

class Token {
	
	public:
		int identifierIndex;
		TokenName name;
	private:
		
};

#endif