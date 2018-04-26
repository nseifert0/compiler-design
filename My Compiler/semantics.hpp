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