#ifndef SEMANTICS_HPP
#define SEMANTICS_HPP

#include "token.hpp"
#include "type.hpp"
#include "expr.hpp"

class Semantics {
	public:
		//Semantics for Types
		Type* basicType(Token t) {
			switch(t.name) {
				case Keyword_Void:
					return new VoidType;
					break;
				case Keyword_Bool:
					return new BoolType;
					break;
				case Keyword_Int:
					return new IntType;
					break;
				case Keyword_Float:
					return new FloatType;
					break;
				case Keyword_Char:
					return new CharType;
					break;
			}
		};
		
		
		//Semantics for Expressions
		Expr* primaryExpression(Token t) {
			switch(t.name) {
				case Decimal_Integer_Literal:
					return new IntegerLiteralExpr(t.integerValue);
					break;
				case Hexadecimal_Integer_Literal:
					return new IntegerLiteralExpr(t.integerValue);
					break;
				case Binary_Integer_Literal:
					return new IntegerLiteralExpr(t.integerValue);
					break;
				case Floating_Point_Literal:
					return new FloatLiteralExpr(t.floatValue);
					break;
				case Boolean_Literal:
					if (t.blt == True)
						return new BooleanLiteralExpr(true);
					else
						return new BooleanLiteralExpr(false);
					break;
				case Character_Literal:
					return new CharacterLiteralExpr(t.charVal);
					break;
			}
		};
};

#endif