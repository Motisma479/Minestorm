#include <stdio.h>
#include <raylib.h>
#include "game.h"




int main(void)
{
	Game game = {0};
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);
	

	return 0;
}
