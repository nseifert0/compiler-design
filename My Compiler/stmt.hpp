//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef STMT_HPP
#define STMT_HPP

enum whatStmt {
	stmtIsTest,
};

class Stmt {
	public:
		Stmt(whatStmt S)
			: mStmt(S) {
				
		}
		
		whatStmt mStmt;
		
};

#endif