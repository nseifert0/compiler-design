#ifndef TOKEN_HPP
#define TOKEN_HPP

enum TokType {
	LeftBrace,
	RightBrace,
	LeftParen,
	RightParen,
	LeftBracket,
	RightBracket,
	Comma,
	Semicolon,
	Colon,
	RelationalOp,
	ArithmeticOp,
	BitwiseOp,
	LogicalOp,
	ConditionalOp,
	AssignmentOp,
	KeywAnd,
	KeywBool,
	KeywChar,
	KeywDef,
	KeywElse,
	KeywFalse,
	KeywFloat,
	KeywIf,
	KeywInt,
	KeywLet,
	KeywNot,
	KeywOr,
	KeywTrue,
	KeywVar,
	Identifier,
	DecimalIntegerLiteral,
	HexadecimalIntegerLiteral,
	BinaryIntegerLiteral,
	FloatingPointLiteral,
	BooleanLiteral,
	CharacterLiteral,
	StringLiteral
};

class Token {
	
	public:
		
	private:
		
};

#endif