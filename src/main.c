#include "game.h"

int main()
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
