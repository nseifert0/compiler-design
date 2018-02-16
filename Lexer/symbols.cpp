#include "symbols.hpp"

void Symbols::addSymbol(std::string s) {
	symbolTable.insert(std::make_pair(s, numberOfSymbols));
	numberOfSymbols++;
}

int Symbols::matchSymbol(std::string s) {
	std::map<std::string, int>::iterator it;
	it = symbolTable.begin();
	while(it != symbolTable.end()) {
		if(it->first == s) {
			return it->second;
		}
		it++;
	}
	return -1;
}