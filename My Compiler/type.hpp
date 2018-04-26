//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef TYPE_HPP
#define TYPE_HPP

enum whatType {
	typeIsTest,
	typeIsBool,
	typeIsChar,
};

class Type {
	public:
		Type(whatType T)
			: mType(T) {
				
		}
		
	private:
		whatType mType;
		
};

#endif