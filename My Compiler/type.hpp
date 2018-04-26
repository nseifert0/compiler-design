//Nicholas Seifert
//Compiler Design - Spring 2018

//TODO: Implement Function Type

#ifndef TYPE_HPP
#define TYPE_HPP

enum whatType {
	typeIsTest,
	typeIsVoid,
	typeIsBool,
	typeIsInt,
	typeIsFloat,
	typeIsChar,
	typeIsPntr,
	typeIsRefr
};

class Type {
	public:
	    Type() {
		}
		
		Type(whatType T)
			: mType(T) {				
		}	
		
		whatType mType;		
};

class VoidType : Type {
	public:
		VoidType() {
			mType = typeIsVoid;
		}		
};

class BoolType : Type {
	public:
		BoolType() {
			mType = typeIsBool;
		}		
};

class IntType : Type {
	public:
		IntType() {
			mType = typeIsInt;
		}		
};

class FloatType : Type {
	public:
		FloatType() {
			mType = typeIsFloat;
		}		
};

class CharType : Type {
	public:
		CharType() {
			mType = typeIsChar;
		}		
};

class PntrType : Type {
	public:
		PntrType(Type* whatItPntsTo)
			: pntsTo(whatItPntsTo) {
				mType = typeIsPntr;
		}
		
	Type* pntsTo;
};

class RefrType : Type {
	public:
		RefrType(Type* whatItRefsTo)
			: refsTo(whatItRefsTo) {
				mType = typeIsRefr;
		}
		
	Type* refsTo;
};


#endif