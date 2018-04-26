//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef EXPR_HPP
#define EXPR_HPP

enum whatExpr {
	exprIsTest,
};

class Expr {
	public:
		Expr(whatExpr E)
			: mExpr(E) {
				
		}
		
	private:
		whatExpr mExpr;
		
};

#endif