#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <cstdlib>
#include <string>

void fatalError(std::string errorMessage)
{
	std::cerr << errorMessage;

	std::cout << "\n\nPress Enter to quit..." << std::endl;
	std::cin.get();

	exit(1);
}


#endif // ERROR_H_