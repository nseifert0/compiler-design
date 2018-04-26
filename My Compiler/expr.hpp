//Nicholas Seifert
//Compiler Design - Spring 2018
//TODO: Maybe implement string literal

#ifndef EXPR_HPP
#define EXPR_HPP

class Type;

enum whatExpr {
	exprIsTest,
	primaryExpression,
	postfixExpression,
	argumentList,
	unaryExpression,
	castExpression,
	multiplicativeExpression,
	additiveExpression,
	shiftExpression,
	relationalExpression,
	equalityExpression,
	bitwiseAndExpression,
	bitwiseXorExpression,
	bitwiseOrExpression,
	logicalAndExpression,
	logicalOrExpression,
	conditionalExpression,
	assignmentExpression,
};

enum whatPrimaryExpr {
	literal,
	identifier,
	parenthesizedPrimary
};

enum whatPostfixExpr {
	parenthesizedPostfix,
	bracketed
};

enum whatUnaryExpr {
	positive,
	negative,
	complement,
	opposite,
	address,
	dereference,
};

enum whatMultiplicativeExpr {
	multiply,
	divide,
	modulo
};

enum whatAdditiveExpr {
	add,
	subtract
};

enum whatShiftExpr {
	left,
	right
};

enum whatRelationalExpr {
	lessThan,
	greaterThan,
	lessThanOrEqual,
	greaterThanOrEqual
};

enum whatEqualityExpr {
	equal,
	notEqual
};

enum whatLiteralExpr {
	eBool,
	eInt,
	eFloat
};

union LiteralValue {
	char charValue;
	int intValue;
	double floatValue;
};

class Expr {
	public:
		Expr(whatExpr e)
			: mWhatExpr(e) {
				
		}
		
		whatExpr mWhatExpr;		
};

class PrimaryExpr : protected Expr {
	public:
		PrimaryExpr(whatPrimaryExpr pE)
			: Expr(primaryExpression), mWhatPrimaryExpr(pE) {
		}
		
		whatPrimaryExpr mWhatPrimaryExpr;
};

class LiteralExpr : protected PrimaryExpr {
	public:
		LiteralExpr(whatLiteralExpr lE, LiteralValue v)
			: PrimaryExpr(literal), value(v) {
		}
		
		whatLiteralExpr mWhatLiteralExpr;
		LiteralValue value;
};

class IdentifierExpr : protected PrimaryExpr {
	public:
		IdentifierExpr()
			: PrimaryExpr(literal) {
		}
};

class ParenthesizedPrimaryExpr : protected PrimaryExpr {
	public:
		ParenthesizedPrimaryExpr(Expr* e)
			: PrimaryExpr(parenthesizedPrimary), innerExpr(e) {
		}
		
		Expr* innerExpr;
};

class ArgumentListExpr : protected Expr {
	public:
		ArgumentListExpr(Expr* l, Expr* r)
			: Expr(argumentList), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class UnaryOperatorExpr :  protected Expr {
	public:
		UnaryOperatorExpr(whatUnaryExpr uE, Expr* arg)
			: Expr(unaryExpression), mWhatUnaryExpr(uE), argument(arg) {
		}
		
		whatUnaryExpr mWhatUnaryExpr;
		Expr* argument;
};

class CastExpr : protected Expr {
	public:
		CastExpr(Expr* arg, Type* cT)
			: Expr(castExpression), argument(arg), castType(cT) {
		}
		
		Expr* argument;
		Type* castType;
};

#endif