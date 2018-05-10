//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef STMT_HPP
#define STMT_HPP

class Expr;
class Decl;

enum whatStmt {
	stmtIsTest,
	blockStatement,
	whenStatement,
	statementSequence,
	ifStatement,
	ifElseStatement,
	whileStatement,
	breakStatement,
	continueStatement,
	returnStatement,
	returnWithExpressionStatement,
	returnWithoutExpressionStatement,
	declarationStatement,
	expressionStatement
};

class Stmt {
	public:
		Stmt(whatStmt S)
			: mWhatStmt(S) {
				
		}
		
		whatStmt mWhatStmt;
};

class BlockStmt : public Stmt {
	public:
		BlockStmt(Stmt* arg)
			: Stmt(blockStatement), argument(arg) {
		}
		
		Stmt* argument;
};

class WhenStmt : public Stmt {
	
};

class StmtSequence : public Stmt {
	public:
		StmtSequence(Stmt* l, Stmt* r)
			: Stmt(statementSequence), lhs(l), rhs(r) {
		}
		
		Stmt* lhs;
		Stmt* rhs;
};

class IfStmt : public Stmt {
	public:
		IfStmt(Expr* cond, Stmt* res)
			: Stmt(ifStatement), condition(cond), result(res) {
		}

		Expr* condition;
		Stmt* result;
};

class IfElseStmt : public Stmt {
	public:
		IfElseStmt(Expr* cond, Stmt* tB, Stmt* fB)
			: Stmt(ifElseStatement), condition(cond), trueBranch(tB), falseBranch(fB) {
		}

		Expr* condition;
		Stmt* trueBranch;
		Stmt* falseBranch;
};

class WhileStmt : public Stmt {
	public:
		WhileStmt(Expr* cond, Stmt* res)
			: Stmt(whileStatement), condition(cond), result(res) {
		}

		Expr* condition;
		Stmt* result;
};

class BreakStmt : public Stmt {
	public:
		BreakStmt()
			: Stmt(breakStatement) {
		}
};

class ContinueStmt : public Stmt {
	public:
		ContinueStmt()
			: Stmt(continueStatement) {
		}
};

class ReturnStmt : public Stmt {
	
};

class ReturnWithExpressionStmt : public Stmt {
	public:
		ReturnWithExpressionStmt(Expr* rE)
			: Stmt(returnWithExpressionStatement), returnExpression(rE) {
		}
		
		Expr* returnExpression;
};

class ReturnWithoutExpressionStmt : public Stmt {
	public:
		ReturnWithoutExpressionStmt()
			: Stmt(returnWithoutExpressionStatement) {
		}
};

class DeclarationStmt : public Stmt {
	public:
		DeclarationStmt(Decl* d)
			: Stmt(declarationStatement), declaration(d) {
		}
		
		Decl* declaration;
};

class ExpressionStmt : public Stmt {
	public:
		ExpressionStmt(Expr* e)
			: Stmt(expressionStatement), expression(e) {
		}
		
		Expr* expression;
};

#endif