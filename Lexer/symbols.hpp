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
		int matchSymbol(std::string);
		
	private:
		std::map<std::string, int> symbolTable;
		int numberOfSymbols;
};

#endif