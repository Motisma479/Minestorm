#include "game.h"


static int frameCount = 0;

bool initGame(Game* game)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "[--MATHIEU-VICTOR-OSVALDO--GP1--MINESTORM PROJECT--ISART DIGITAL--]");
	SetTargetFPS(60);

	game->gamePaused = false;
	game->gameIsRunning = true;
	game->enemiesCount = 0;
	loadGameData(game);

	initPlayer(&game->player);
	game->player.active = true;

	return game->gameIsRunning;
}
void processInput(Game* game)
{
	//if (IsKeyPressed(KEY_F) && game->gameIsRunning && !game->layer.active)
	//{
		//initLayer(&game->layer);
		//game->layer.active = true;
	//}

	if (IsKeyDown(KEY_ESCAPE) && game->gameIsRunning)
	{
		game->gameIsRunning = false;
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		game->gamePaused = !game->gamePaused;
	}

 	inputsPlayer(&game->player);
}
void updateGame(Game* game)
{
	float deltaTime = GetFrameTime();
	//if (game->layer.layerEnd && !game->player.active)
	//{
		//initPlayer(&game->player);
		//game->player.active = true;
	//}
	if (!game->gamePaused)
	{
		//TODO : updating all game objects

		//update enemies
		//for(int i = 0; i < game->enemiesCount; i++)
		//{
			//updateEnemy(&game->enemies[i],deltaTime);
		//}

		updateLayer(&game->layer,deltaTime);
		updatePlayer(&game->player, deltaTime);

	}
	else
	{
		//TODO
		frameCount++;
	}
}

void runGameLoop(Game* game)
{
	while (!WindowShouldClose() && game->gameIsRunning) 
	{
		processInput(game);
		updateGame(game);
		drawGame(game);
	}
}
void drawGame(Game* game)
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	drawGameBackground(game);

	if (!game->gamePaused)
	{
		//display all game objects

		//draw enemies
		//for(int i = 0; i < game->enemiesCount; i++)
		//{
			//drawEnemy(&game->enemies[i],game->gameTexture);
		//}

		drawLayer(&game->layer,game->gameTexture);

		drawPlayer(&game->player,game->gameTexture);
	}
	else
	{
		pauseGame(game);
	}

	EndDrawing();
}
void shutdown(Game* game)
{
	game->gameIsRunning = false;
	if (!game->gameIsRunning)
	{
		unloadGameData(game);
		CloseWindow();
	}
}

void loadGameData(Game* game)
{
	game->background = LoadTexture("assets/background.png");
	game->foreground =  LoadTexture("assets/foreground.png");
	game->gameTexture = LoadTexture("assets/mines.png");
}
void unloadGameData(Game* game)
{
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
	UnloadTexture(game->gameTexture);
}

void drawGameBackground(Game* game)
{
	DrawTexture(game->background, 0, 0, WHITE);
	DrawTexture(game->foreground, 0, 0, WHITE);
}

void pauseGame(Game* game)
{
	if ((frameCount / 30) % 2) DrawText("GAME PAUSED",
		(int)SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED",50) + 200, (int)SCREEN_HEIGHT/2 -50,50,WHITE);
}

void addEnemyToGame(Game* game)
{
	//Enemy enemy = {0};
	//enemy.type = FLOATING_MINE;

	//initEnemy(&enemy);

	//game->enemies[game->enemiesCount] = enemy;
	//game->enemiesCount += 1;	

}