#include "symbols.hpp"

int Symbols::addSymbol(std::string s) {
	numberOfSymbols++;
	symbolTable.insert(std::make_pair(s, numberOfSymbols));
	return numberOfSymbols;
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
	return addSymbol(s);
}

std::string Symbols::matchSymbol(int tableIndex) {
	std::map<std::string, int>::iterator it;
	it = symbolTable.begin();
	while(it != symbolTable.end()) {
		if(it->second == tableIndex) {
			return it->first;
		}
		it++;
	}
	return "";
}