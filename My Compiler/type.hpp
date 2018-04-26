//Nicholas Seifert
//Compiler Design - Spring 2018

//TODO: Implement Function Type

#ifndef TYPE_HPP
#define TYPE_HPP

class Expr;

enum whatType {
	typeIsTest,
	basic,
	postfix,
	reference
};

enum whatBasicType {
	tVoid,
	tBool,
	tInt,
	tFloat,
	tChar,
	tFunction,
	tParenthesized,
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


class BasicType : public Type {
	public:
		BasicType(whatBasicType bT)
			: Type(basic), mWhatBasicType(bT) {
		}
		
		whatBasicType mWhatBasicType;
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