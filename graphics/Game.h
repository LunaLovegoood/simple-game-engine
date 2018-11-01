// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"


// Represents possible game states
enum class GameState{ PLAY, EXIT };


class Game
{
public:
	void run();

private:
	SDL_Window* window_{ nullptr }; // window handle
	unsigned short screenWidth_{ 800 };
	unsigned short screenHeight_{ 600 };

	GameState gameState_{ GameState::PLAY }; // current game state

	GLSLProgram colorProgram_{};

	void initGame();
	void createWindow();
	void initGLContext();
	void initGlew();
	void initShaders();

	void gameLoop();

	void processInput();
	void drawGame();
};

#endif // GAME_H_