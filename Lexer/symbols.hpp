//Nicholas Seifert
//Compiler Design - Spring 2018

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <map>
#include <string>

class Symbols {
	public:
		Symbols()
			: numberOfSymbols(0)
		{
		
		}
		
		int addSymbol(std::string);
		int matchSymbol(std::string);
		std::string matchSymbol(int);
		
	private:
		std::map<std::string, int> symbolTable;
		int numberOfSymbols;
};

#endif