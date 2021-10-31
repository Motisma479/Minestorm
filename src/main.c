#include "game.h"
#include "player.h"
#include "levels.h"
#include "draw.h"
#include "input.h"

int main()
{
	Game game = {0};

	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"MATHIEU-OSVALDO-VICTOR");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	game.state = GS_MENU;

	initPlayer(&game.player[0], (Vector2d){SCREEN_WIDTH / 3.0f,
				   SCREEN_HEIGHT / 2.0f});
	initPlayer(&game.player[1], (Vector2d){SCREEN_WIDTH / 1.5f,
				   SCREEN_HEIGHT / 2.0f});
	initLevel1(&game);

	game.atlas = LoadTexture("assets/mines.png");
	game.background = LoadTexture("assets/background.png");
	game.foreground = LoadTexture("assets/foreground.png");

	while (!WindowShouldClose() && game.state != GS_CLOSE)
	{
		game.ticksCount = GetFrameTime();
		getInput(&game);

		//We start drawing the background before updating
		//because we want to draw the collisions boxes immediately after updating them
		BeginDrawing();
		DrawTextureEx(game.background, (Vector2){0, 0}, 0, 1.0f, WHITE);
		updateGame(&game);
		drawGame(&game); 
	}

	UnloadTexture(game.atlas);
	UnloadTexture(game.background);
	UnloadTexture(game.foreground);

	CloseWindow();
	return 0;
}
