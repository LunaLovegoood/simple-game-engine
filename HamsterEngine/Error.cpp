// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "Error.h"

#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>

// Prints out error message and exits the program
void fatalError(const std::string &errorMessage)
{
	std::cerr << errorMessage;

	std::cout << "\n\nPress Enter to quit..." << std::endl;
	std::cin.get();

	SDL_Quit();
	exit(1);
}