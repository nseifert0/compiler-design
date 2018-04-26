//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef DECL_HPP
#define DECL_HPP

enum whatDecl {
	declIsTest,
};

class Decl {
	public:
		Decl(whatDecl D)
			: mDecl(D) {
				
		}
		
		whatDecl mDecl;
		
};

#endif