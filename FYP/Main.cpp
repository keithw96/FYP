#include "Game.h"

/// <summary>
/// Main entry point
/// </summary>
/// <returns></returns>
int main()
{
	srand(time(NULL));

	Game game;
	game.update();

	return 0;
}