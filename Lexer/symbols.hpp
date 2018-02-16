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
		
		void addSymbol(std::string);
		void matchSymbol(std::string);
		
	private:
		std::map<std::string, int> symbolTable;
		int numberOfSymbols;
};

#endif