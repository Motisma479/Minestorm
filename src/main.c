#include <stdio.h>
#include "game.h"



int main(void)
{
    printf("MINESTORM GAME\n");

    Game game;
    bool success = initGame(&game);
    if(success)
    {
        runLoop(&game);
    }
    Shutdown(&game);
    return 0;
}