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
					return new BasicType(tVoid);
					break;
				case Keyword_Bool:
					return new BasicType(tBool);
					break;
				case Keyword_Int:
					return new BasicType(tInt);
					break;
				case Keyword_Float:
					return new BasicType(tFloat);
					break;
				case Keyword_Char:
					return new BasicType(tChar);
					break;
			}
		};
		
		
		//Semantics for Expressions
		Expr* primaryExpression(Token t) {
			switch(t.name) {
				case Decimal_Integer_Literal:
					LiteralValue lV = {t.integerValue};
					return new LiteralExpr(eInt, lV);
					break;
				/*
				case Hexadecimal_Integer_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case Binary_Integer_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case Floating_Point_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case Boolean_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case Character_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case String_Literal:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				case Identifier:
					return new LiteralExpr(eInt, LiteralValue(t.integerValue));
					break;
				*/
			}
		};
};

#endif