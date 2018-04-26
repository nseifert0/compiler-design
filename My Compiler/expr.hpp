//Nicholas Seifert
//Compiler Design - Spring 2018
//TODO: Maybe implement string literal

#ifndef EXPR_HPP
#define EXPR_HPP

//Allow type to be used but defined later
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
	bitwiseXOrExpression,
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

class MultiplicativeExpr : protected Expr {
	public: 
		MultiplicativeExpr(whatMultiplicativeExpr mE, Expr* l, Expr* r)
			: Expr(multiplicativeExpression), mWhatMultiplicativeExpr(mE), lhs(l), rhs(r) {
		}
		
		whatMultiplicativeExpr mWhatMultiplicativeExpr;
		Expr* lhs;
		Expr* rhs;
};

class AdditiveExpr : protected Expr {
	public: 
		AdditiveExpr(whatAdditiveExpr aE, Expr* l, Expr* r)
			: Expr(additiveExpression), mWhatAdditiveExpr(aE), lhs(l), rhs(r) {
		}
		
		whatAdditiveExpr mWhatAdditiveExpr;
		Expr* lhs;
		Expr* rhs;
};

class ShiftExpr : protected Expr {
	public: 
		ShiftExpr(whatShiftExpr sE, Expr* l, Expr* r)
			: Expr(shiftExpression), mWhatShiftExpr(sE), lhs(l), rhs(r) {
		}
		
		whatShiftExpr mWhatShiftExpr;
		Expr* lhs;
		Expr* rhs;
};

class RelationalExpr : protected Expr {
	public: 
		RelationalExpr(whatRelationalExpr rE, Expr* l, Expr* r)
			: Expr(relationalExpression), mWhatRelationalExpr(rE), lhs(l), rhs(r) {
		}
		
		whatRelationalExpr mWhatRelationalExpr;
		Expr* lhs;
		Expr* rhs;
};

class EqualityExpr : protected Expr {
	public: 
		EqualityExpr(whatEqualityExpr eE, Expr* l, Expr* r)
			: Expr(equalityExpression), mWhatEqualityExpr(eE), lhs(l), rhs(r) {
		}
		
		whatEqualityExpr mWhatEqualityExpr;
		Expr* lhs;
		Expr* rhs;
};

class BitwiseAndExpr : protected Expr {
	public: 
		BitwiseAndExpr(Expr* l, Expr* r)
			: Expr(bitwiseAndExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class BitwiseXOrExpr : protected Expr {
	public: 
		BitwiseXOrExpr(Expr* l, Expr* r)
			: Expr(bitwiseXOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class BitwiseOrExpr : protected Expr {
	public: 
		BitwiseOrExpr(Expr* l, Expr* r)
			: Expr(bitwiseOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class LogicalAndExpr : protected Expr {
	public: 
		LogicalAndExpr(Expr* l, Expr* r)
			: Expr(logicalAndExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class LogicalOrExpr : protected Expr {
	public: 
		LogicalOrExpr(Expr* l, Expr* r)
			: Expr(logicalOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class ConditionalExpr : protected Expr {
	public: 
		ConditionalExpr(Expr* cond, Expr* tB, Expr* fB)
			: Expr(conditionalExpression), condition(cond), trueBranch(tB), falseBranch(fB) {
		}
		
		Expr* condition;
		Expr* trueBranch;
		Expr* falseBranch;
};

class AssignmentExpr : protected Expr {
	public: 
		AssignmentExpr(Expr* l, Expr* r)
			: Expr(assignmentExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

#endif