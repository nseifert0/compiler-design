//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef DECL_HPP
#define DECL_HPP

#include <vector>
#include <string>

//Need to fix how identifiers are stored to get this to work
class Symbol;
class Type;
class Expr;
class Stmt;

enum whatDecl {
	declIsTest,
	program,
	declarationSequence,
	variableDefinition,
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
		//name should correspond to an entry in the symbol table
		std::string* name = new std::string("");
		
};

using DeclList = std::vector<Decl*>;

class ProgramDecl : public Decl {
	public:
		ProgramDecl(DeclList& d)
			: Decl(program), declarations(d) {
		}
		
		DeclList declarations;
};

class DeclSequence : public Decl {
	public:
		DeclSequence(Decl* l, Decl* r)
			: Decl(declarationSequence), lhs(l), rhs(r) {
		}
		
		Decl* lhs;
		Decl* rhs;
};

class VariableDefinitionDecl : public Decl {
	public:
		VariableDefinitionDecl(Symbol* i, Type* t, Expr* e)
			: Decl(variableDefinition), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class VariableDefinitionWithExpressionDecl : public Decl {
	public:
		VariableDefinitionWithExpressionDecl(Symbol* i, Type* t, Expr* e)
			: Decl(variableDefinitionWithExpression), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class VariableDefinitionWithoutExpressionDecl : public Decl {
	public:
		VariableDefinitionWithoutExpressionDecl(Symbol* i, Type* t)
			: Decl(variableDefinitionWithExpression), identifier(i), type(t) {
		}
		
		Symbol* identifier;
		Type* type;
};

class ConstantDefinitionDecl : public Decl {
	public:
		ConstantDefinitionDecl(Symbol* i, Type* t, Expr* e)
			: Decl(constantDefinition), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class ValueDefinitionDecl : public Decl {
	public:
		ValueDefinitionDecl(Symbol* i, Type* t, Expr* e)
			: Decl(valueDefinition), identifier(i), type(t), expression(e) {
		}
		
		Symbol* identifier;
		Type* type;
		Expr* expression;
};

class FunctionDefinitionDecl : public Decl {
	public:
		FunctionDefinitionDecl(Symbol* i, DeclList& p, Type* t, Stmt* s)
			: Decl(functionDefinition), identifier(i), parameters(p), type(t), body(s) {
		}
		
		Symbol* identifier;
		DeclList parameters;
		Type* type;
		Stmt* body;
};

class ParameterListDecl : public Decl {
	public:
		ParameterListDecl(Decl* l, Decl* r)
			: Decl(parameterList), lhs(l), rhs(r) {
		}
		
		Decl* lhs;
		Decl* rhs;
};

class ParameterDecl :  public Decl {
	public:
		ParameterDecl(Symbol* i, Type* t)
			: Decl(parameter), identifier(i), type(t) {
		}
		
		Symbol* identifier;
		Type* type;
};

class TypedDecl : public Decl { 
	public:
		TypedDecl(Symbol* i, Type* t)
			: Decl(parameter), identifier(i), type(t) {
		}
		
		Symbol* identifier;
		Type* type;
};

#endif