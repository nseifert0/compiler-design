//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef DECL_HPP
#define DECL_HPP

//Need to fix how identifiers are stored to get this to work
class Symbol;
class Type;
class Expr;
class Stmt;


enum whatDecl {
	declIsTest,
	program,
	declarationSequence,
	variableDefinitionWithExpression,
	variableDefinitionWithoutExpression,
	constantDefinition,
	valueDefinition,
	functionDefinition,
	parameterList,
	parameter
};

class Decl {
	public:
		Decl(whatDecl D)
			: mWhatDecl(D) {
				
		}
		
		whatDecl mWhatDecl;		
};

class Program : Decl {
	public:
		Program(Decl* d)
			: Decl(program), declaration(d) {
		}
		
		Decl* declaration;
};

class DeclSequence : Decl {
	public:
		DeclSequence(Decl* l, Decl* r)
			: Decl(declarationSequence), lhs(l), rhs(r) {
		}
		
		Decl* lhs;
		Decl* rhs;
};

class VariableDefinitionWithExpression : Decl {
	public:
		VariableDefinitionWithExpression(Symbol* i, Type* t, Expr* e)
			: Decl(variableDefinitionWithExpression), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class VariableDefinitionWithoutExpression : Decl {
	public:
		VariableDefinitionWithoutExpression(Symbol* i, Type* t)
			: Decl(variableDefinitionWithExpression), identifier(i), type(t) {
		}
		
		Symbol* identifier;
		Type* type;
};

class ConstantDefinition : Decl {
	public:
		ConstantDefinition(Symbol* i, Type* t, Expr* e)
			: Decl(constantDefinition), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class ValueDefinition : Decl {
	public:
		ValueDefinition(Symbol* i, Type* t, Expr* e)
			: Decl(valueDefinition), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class FunctionDefinition : Decl {
	public:
		FunctionDefinition(Symbol* i, Decl* p, Type* t, Stmt* s)
			: Decl(functionDefinition), identifier(i), parameters(p), type(t), statement(s) {
		}
		
		Symbol* identifier;
		Decl* parameters;
		Type* type;
		Stmt* statement;
};

class ParameterList : Decl {
	public:
		ParameterList(Decl* l, Decl* r)
			: Decl(parameterList), lhs(l), rhs(r) {
		}
		
		Decl* lhs;
		Decl* rhs;
};

class Parameter : Decl {
	public:
		Parameter(Symbol* i, Type* t)
			: Decl(parameter), identifier(i), type(t) {
		}
		
		Symbol* identifier;
		Type* type;
};


#endif