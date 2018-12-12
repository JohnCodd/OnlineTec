#include <SDL.h>
#include <stdio.h>
#include "Game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	Game game(60, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.Run();

	return 0;
}