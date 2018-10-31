#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include <GL/glew.h>


// Represents possible game states
enum class GameState{ PLAY, EXIT };


class Game
{
public:
	Game() {}
	~Game();

	void run();

private:
	SDL_Window* window_{ nullptr }; // window handle
	unsigned short screenWidth_{ 800 };
	unsigned short screenHeight_{ 600 };

	GameState gameState_{ GameState::PLAY }; // current game state

	void initGame();
	void createWindow();
	void initGLContext();
	void initGlew();

	void gameLoop();

	void processInput();
	void drawGame();
};

#endif // GAME_H_