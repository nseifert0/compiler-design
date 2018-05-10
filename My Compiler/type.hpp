//Nicholas Seifert
//Compiler Design - Spring 2018

//TODO: Implement Function Type

#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>

class Expr;

enum whatType {
	typeIsTest,
	basic,
	postfix,
	reference,
	function,
	typeList,
	tVoid,
	tBool,
	tInt,
	tFloat,
	tChar,
	tFunction,
	tParenthesized
};

enum whatPostfixType {
	pointer,
	tConst,
	tVolatile,
	arrayWithArgument,
	arrayWithoutArgument,
};

class Type {
	public:
		Type(whatType t)
			: mWhatType(t) {				
		}	
		
		whatType mWhatType;		
};

using TypeList = std::vector<Type*>;

class VoidType : public Type {
	public:
		VoidType()
			: Type(tVoid) {
		}
};


class BoolType : public Type {
	public:
		BoolType()
			: Type(tBool) {
		}
	
};

class CharType : public Type {
	public:
		CharType()
			: Type(tChar) {
		}
};

class IntType : public Type {
	public:
		IntType()
			: Type(tInt) {
		}
};

class FloatType : public Type {
	public:
		FloatType()
			: Type(tFloat) {
		}	
};

class FunctionType : public Type {
	public:
		FunctionType(TypeList& pT, Type* rT)
			: Type(function), parameterType(pT), returnType(rT) {
		}
		
		TypeList parameterType;
		Type* returnType;
};

class PostfixType : public Type {
	public:
		PostfixType(whatPostfixType pT, Type* base)
			: Type(postfix), mWhatPostfixType(pT), baseType(base) {
		}
		
		whatPostfixType mWhatPostfixType;
		Type* baseType;
};


class ArrayWithArgumentType : public PostfixType {
	public:
		ArrayWithArgumentType(Expr* arg, Type* base)
			: PostfixType(arrayWithArgument, base), argument(arg) {
		}
		
		Expr* argument;
};


//Implement function type class that extends the BasicType

class ReferenceType : public Type {
	public:
		ReferenceType(Type* refs)
			: Type(reference), baseType(refs) {
		}
		
		Type* baseType;
};


#endif