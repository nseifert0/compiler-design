#include <iostream>
#include <fstream>
#include <string>

#include "lexer.hpp"

int main() {
	std::ifstream file ("Input.txt");
	
	char c;
	char d;
	
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::cout << file.eof() << "\n";
			c = file.get();
			std::cout << c << "\n";
			std::cout << file.peek() << "\n";
			std::cout << file.eof() << "\n";
		}
    file.close();
  }
	return 0;
}