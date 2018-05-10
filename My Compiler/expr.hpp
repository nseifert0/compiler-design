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
	booleanLiteral,
	characterLiteral,
	integerLiteral,
	floatLiteral,
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

class PrimaryExpr : public Expr {
	public:
		PrimaryExpr(whatPrimaryExpr pE)
			: Expr(primaryExpression), mWhatPrimaryExpr(pE) {
		}
		
		whatPrimaryExpr mWhatPrimaryExpr;
};

class BooleanLiteralExpr : public PrimaryExpr {
	public:
		BooleanLiteralExpr(bool bV)
			: PrimaryExpr(booleanLiteral), boolValue(bV) {
		}

		bool boolValue;
};

class IntegerLiteralExpr : public PrimaryExpr {
	public:
		IntegerLiteralExpr(int iV)
			: PrimaryExpr(integerLiteral), intValue(iV) {
		}

		int intValue;
};

class FloatLiteralExpr : public PrimaryExpr {
	public:
		FloatLiteralExpr(double fV)
			: PrimaryExpr(floatLiteral), floatValue(fV) {
		}

		double floatValue;
};

class CharacterLiteralExpr : public PrimaryExpr {
	public:
		CharacterLiteralExpr(int cV)
			: PrimaryExpr(characterLiteral), charValue(cV) {
		}

		char charValue;
};

class IdentifierExpr : public PrimaryExpr {
	public:
		IdentifierExpr()
			: PrimaryExpr(identifier) {
		}
};

class ParenthesizedPrimaryExpr : public PrimaryExpr {
	public:
		ParenthesizedPrimaryExpr(Expr* e)
			: PrimaryExpr(parenthesizedPrimary), innerExpr(e) {
		}
		
		Expr* innerExpr;
};

class ArgumentListExpr : public Expr {
	public:
		ArgumentListExpr(Expr* l, Expr* r)
			: Expr(argumentList), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class UnaryOperatorExpr :  public Expr {
	public:
		UnaryOperatorExpr(whatUnaryExpr uE, Expr* arg)
			: Expr(unaryExpression), mWhatUnaryExpr(uE), argument(arg) {
		}
		
		whatUnaryExpr mWhatUnaryExpr;
		Expr* argument;
};

class BinaryOperatorExpr : public Expr {
	
};

class CastExpr : public Expr {
	public:
		CastExpr(Expr* arg, Type* cT)
			: Expr(castExpression), argument(arg), castType(cT) {
		}
		
		Expr* argument;
		Type* castType;
};

class MultiplicativeExpr : public Expr {
	public: 
		MultiplicativeExpr(whatMultiplicativeExpr mE, Expr* l, Expr* r)
			: Expr(multiplicativeExpression), mWhatMultiplicativeExpr(mE), lhs(l), rhs(r) {
		}
		
		whatMultiplicativeExpr mWhatMultiplicativeExpr;
		Expr* lhs;
		Expr* rhs;
};

class AdditiveExpr : public Expr {
	public: 
		AdditiveExpr(whatAdditiveExpr aE, Expr* l, Expr* r)
			: Expr(additiveExpression), mWhatAdditiveExpr(aE), lhs(l), rhs(r) {
		}
		
		whatAdditiveExpr mWhatAdditiveExpr;
		Expr* lhs;
		Expr* rhs;
};

class ShiftExpr : public Expr {
	public: 
		ShiftExpr(whatShiftExpr sE, Expr* l, Expr* r)
			: Expr(shiftExpression), mWhatShiftExpr(sE), lhs(l), rhs(r) {
		}
		
		whatShiftExpr mWhatShiftExpr;
		Expr* lhs;
		Expr* rhs;
};

class RelationalExpr : public Expr {
	public: 
		RelationalExpr(whatRelationalExpr rE, Expr* l, Expr* r)
			: Expr(relationalExpression), mWhatRelationalExpr(rE), lhs(l), rhs(r) {
		}
		
		whatRelationalExpr mWhatRelationalExpr;
		Expr* lhs;
		Expr* rhs;
};

class EqualityExpr : public Expr {
	public: 
		EqualityExpr(whatEqualityExpr eE, Expr* l, Expr* r)
			: Expr(equalityExpression), mWhatEqualityExpr(eE), lhs(l), rhs(r) {
		}
		
		whatEqualityExpr mWhatEqualityExpr;
		Expr* lhs;
		Expr* rhs;
};

class BitwiseAndExpr : public Expr {
	public: 
		BitwiseAndExpr(Expr* l, Expr* r)
			: Expr(bitwiseAndExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class BitwiseXOrExpr : public Expr {
	public: 
		BitwiseXOrExpr(Expr* l, Expr* r)
			: Expr(bitwiseXOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class BitwiseOrExpr : public Expr {
	public: 
		BitwiseOrExpr(Expr* l, Expr* r)
			: Expr(bitwiseOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class LogicalAndExpr : public Expr {
	public: 
		LogicalAndExpr(Expr* l, Expr* r)
			: Expr(logicalAndExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class LogicalOrExpr : public Expr {
	public: 
		LogicalOrExpr(Expr* l, Expr* r)
			: Expr(logicalOrExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class ConditionalExpr : public Expr {
	public: 
		ConditionalExpr(Expr* cond, Expr* tB, Expr* fB)
			: Expr(conditionalExpression), condition(cond), trueBranch(tB), falseBranch(fB) {
		}
		
		Expr* condition;
		Expr* trueBranch;
		Expr* falseBranch;
};

class AssignmentExpr : public Expr {
	public: 
		AssignmentExpr(Expr* l, Expr* r)
			: Expr(assignmentExpression), lhs(l), rhs(r) {
		}
		
		Expr* lhs;
		Expr* rhs;
};

class CallExpr : public Expr {
	
};

class ConvExpr : public Expr {
	
};

class IndexExpr : public Expr {
	
};

#endif