#include <stdio.h>
#include "game.h"


int main()
{
	printf("OSVALDO LOANDA\n");

	Game game;
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);
	return 0;
}