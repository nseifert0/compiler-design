//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef EXPR_HPP
#define EXPR_HPP

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

#endif