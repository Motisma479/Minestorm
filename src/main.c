#include "game.h"
#include "player.h"
#include "levels.h"
#include "draw.h"
#include "input.h"

int main()
{
	Game game = {0};

	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"MATHIEU-OSVALDO-VICTOR");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	game.state = GS_MENU;

	initPlayer(&game.player[0], (Vector2d){SCREEN_WIDTH / 3.0f,
				   SCREEN_HEIGHT - 200});
	initPlayer(&game.player[1], (Vector2d){SCREEN_WIDTH / 1.5f,
				   SCREEN_HEIGHT - 200});
	initLayer(&game.layer);

	game.atlas = LoadTexture("assets/mines.png");
	game.background = LoadTexture("assets/background.png");
	game.foreground = LoadTexture("assets/foreground.png");
	game.slowDown = 1.0f;
	float goal = 0;
	float deltaTime = 0;
	while (!WindowShouldClose() && game.state != GS_CLOSE)
	{
		deltaTime = GetFrameTime();
		getInput(&game);

		//We start drawing the background before updating
		//because we want to draw the collisions boxes immediately after updating them
		goal = 0;
		BeginDrawing();
		DrawTextureEx(game.background, (Vector2){0, 0}, 0, 1.0f, WHITE);
		game.mineLayerUpdated = false;
		while (goal < deltaTime)
		{
			game.ticksCount = 0.00035;
			updateGame(&game);
			game.mineLayerUpdated = true;
			goal += 0.00035;
		}
		drawGame(&game); 
		game.framesCounter++;
	}

	UnloadTexture(game.atlas);
	UnloadTexture(game.background);
	UnloadTexture(game.foreground);

	CloseWindow();
	return 0;
}
