//Nicholas Seifert
//Compiler Design - Spring 2018

#include "symbols.hpp"

int Symbols::addSymbol(std::string s) {
	numberOfSymbols++;
	symbolTable.insert(std::make_pair(s, numberOfSymbols));
	return numberOfSymbols;
}


//Gets the index of the symbobl in the table
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

//Gets the symbobl from the table based upon the index
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