// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "Game.h"
#include "Sprite.h"
#include "Error.h"

#include <iostream>


// Run the game
void Game::run()
{
	initGame();

	gameLoop();
}

// Initialize everything needed for the game
void Game::initGame()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	createWindow();

	initGLContext();

	initGlew();

	initShaders();

	// Enable double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// White cleaning
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

// Create window
void Game::createWindow()
{
	window_ = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth_, screenHeight_,
		SDL_WINDOW_OPENGL);

	if (!window_)
	{
		fatalError("Failed to open a window!");
	}
}

// Init openGL context
void Game::initGLContext()
{
	auto glContext = SDL_GL_CreateContext(window_);

	if (!glContext)
	{
		fatalError("Failed to create openGL context!");
	}
}

// Initialize glew extension entry points
void Game::initGlew()
{
	auto error = glewInit();

	if (error != GLEW_OK)
	{
		fatalError("Failed to initialize GLEW!");
	}
}

// Initialize shaders
void Game::initShaders()
{
	colorProgram_.compileShaders("shaders/color_shading.vert", "shaders/color_shading.frag");

	colorProgram_.addAttribute("vertexPosition");

	colorProgram_.linkShaders();
}

// Main game loop
void Game::gameLoop()
{
	while (gameState_ != GameState::EXIT)
	{
		processInput();

		drawGame();
	}
}

// Processes user's input
void Game::processInput()
{
	SDL_Event userEvent{};

	// Handle event
	while (SDL_PollEvent(&userEvent))
	{
		switch (userEvent.type)
		{
		case SDL_QUIT:
			gameState_ = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << userEvent.motion.x << " " << userEvent.motion.y << std::endl;
			break;
		}
	}
}

// Draw stuff
void Game::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorProgram_.use();

	Sprite(-1.0f, -1.0f, 1.0f, 1.0f).draw();

	colorProgram_.unuse();

	// Swap windows
	SDL_GL_SwapWindow(window_);
}