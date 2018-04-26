//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef EXPR_HPP
#define EXPR_HPP

enum whatExpr {
	exprIsTest,
	/*primaryExpression;
	postfixExpression;
	argumentList;
	unaryExpression;
	castExpression;
	multiplicativeExpression;
	additiveExpression;
	shiftExpression;
	relationalExpression;
	equalityExpression;
	bitwiseAndExpression;
	bitwiseXorExpression;
	bitwiseOrExpression;
	logicalAndExpression;
	logicalOrExpression;
	conditionalExpression;
	assignmentExpression;
	*/
};

class Expr {
	public:
		Expr(whatExpr E)
			: mExpr(E) {
				
		}
		
		whatExpr mExpr;
		
};

#endif