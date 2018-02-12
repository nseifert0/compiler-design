#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream file ("Input.txt");
	
	std::string line;
	
	if (file.is_open())
	{
		while ( getline (file,line) )
		{
			std::cout << line << '\n';
		}
    file.close();
  }
	return 0;
}