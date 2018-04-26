//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef STMT_HPP
#define STMT_HPP

class Expr;
class Decl;

enum whatStmt {
	stmtIsTest,
	blockStatement,
	statementSequence,
	ifStatement,
	ifElseStatement,
	whileStatement,
	breakStatement,
	continueStatement,
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

class BlockStmt : protected Stmt {
	public:
		BlockStmt(Stmt* arg)
			: Stmt(blockStatement), argument(arg) {
		}
		
		Stmt* argument;
};

class StmtSequence : protected Stmt {
	public:
		StmtSequence(Stmt* l, Stmt* r)
			: Stmt(statementSequence), lhs(l), rhs(r) {
		}
		
		Stmt* lhs;
		Stmt* rhs;
};

class IfStmt : protected Stmt {
	public:
		IfStmt(Expr* cond, Stmt* res)
			: Stmt(ifStatement), condition(cond), result(res) {
		}

		Expr* condition;
		Stmt* result;
};

class IfElseStmt : protected Stmt {
	public:
		IfElseStmt(Expr* cond, Stmt* tB, Stmt* fB)
			: Stmt(ifElseStatement), condition(cond), trueBranch(tB), falseBranch(fB) {
		}

		Expr* condition;
		Stmt* trueBranch;
		Stmt* falseBranch;
};

class WhileStmt : protected Stmt {
	public:
		WhileStmt(Expr* cond, Stmt* res)
			: Stmt(whileStatement), condition(cond), result(res) {
		}

		Expr* condition;
		Stmt* result;
};

class BreakStmt : protected Stmt {
	public:
		BreakStmt()
			: Stmt(breakStatement) {
		}
};

class ContinueStmt : protected Stmt {
	public:
		ContinueStmt()
			: Stmt(continueStatement) {
		}
};

class ReturnWithExpressionStmt : protected Stmt {
	public:
		ReturnWithExpressionStmt(Expr* rE)
			: Stmt(returnWithExpressionStatement), returnExpression(rE) {
		}
		
		Expr* returnExpression;
};

class ReturnWithoutExpressionStmt : protected Stmt {
	public:
		ReturnWithoutExpressionStmt()
			: Stmt(returnWithoutExpressionStatement) {
		}
};

class DeclarationStatement : protected Stmt {
	public:
		DeclarationStatement(Decl* d)
			: Stmt(declarationStatement), declaration(d) {
		}
		
		Decl* declaration;
};

class ExpressionStatement : protected Stmt {
	public:
		ExpressionStatement(Expr* e)
			: Stmt(expressionStatement), expression(e) {
		}
		
		Expr* expression;
};

#endif