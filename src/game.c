#include "game.h"
#include "draw.h"

//cross->textureCoord[0] = (Rectangle){345, 90, 75, 75};
//ship->textureCoord[0] = (Rectangle){513, 89, 256, 79};

#include <stdlib.h>

// TODO(v.caraulan): NO GLOBALS EVER
static int framesCounter = 0;

bool initGame(Game* game)
{
	game->state = GS_MENU;
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"VICTOR-MATHIEU-OSVALDO");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);

	initPlayer(&game->player);

	for(int i = 0; i < ENEMY_COUNT; i++)
		initEnemy(&game->atlas, &game->enemies[i]);
	loadData(game);
	game->ticksCount = 0;
	return true;
}

void runLoop(Game* game)
{
	while (!WindowShouldClose() && game->state != GS_CLOSE)
	{
		game->ticksCount = GetFrameTime();
		processInput(game);
		updateGame(game);
		drawGame(game, framesCounter);
	}

}
void processInput(Game* game)
{
	if(IsKeyPressed(KEY_SPACE))
	{
		if (game->state == GS_PLAY)
			game->state = GS_PAUSE;
		else if (game->state == GS_PAUSE)
			game->state = GS_PLAY;
	}

	// TODO(v.caraulan): We can have a flag with all input
	if(IsKeyDown(KEY_UP))
		game->player.moving = true;
	else
		game->player.moving = false;

	if(IsKeyPressed(KEY_F))
		game->player.shooting = true;
	if(IsKeyPressed(KEY_ESCAPE))
	{
		if (game->state == GS_MENU)
			game->state = GS_CLOSE;
		if (game->state == GS_PAUSE)
			game->state = GS_MENU;

	}
}

void updateGame(Game* game)
{
	switch(game->state)
	{
		case GS_MENU:
		{
			if (game->player.shooting)
				game->state = GS_PLAY;
			game->player.shooting = false;
			framesCounter++;
		}break;
		case GS_PLAY: 
		case GS_PLAY2:
		{
			if (game->player.shooting)
				gameAddBullet(game,game->player.position);
			updatePlayer(&game->player, game->ticksCount);

			for(int i = 0; i < ENEMY_COUNT; i++)
				updateEnemy(&game->enemies[i], game->ticksCount);

			for(int i = 0; i < game->bulletCount; i++)
			{
				Bullet* bullet = &game->bullets[i];
				updateBullet(bullet,game->ticksCount);
			}
			gameRemoveBullet(game);
			gameStats(game);
			gameIsOver(game);
		}break;
		default:
		{
			framesCounter++;
		}
	}
}

void gameStats(Game* game)
{
	DrawText(TextFormat("Enemy count: %d",gameEnemyAliveCount(game)),10,10,20,PURPLE);
	DrawText(TextFormat("Bullet count: %d",game->bulletCount),10,50,20,PURPLE);
}

void gameAddBullet(Game* game, Vector2 position)
{
	if(game->bulletCount == BULLET_CAPACITY)
		return;

	Bullet bullet = {0};

	initBullet(&bullet,position, game->player.rotation);

	game->bullets[game->bulletCount] = bullet;
	game->bulletCount += 1;
}

void gameRemoveBullet(Game* game)
{
	for(int i = 0; i < game->bulletCount; i++)
	{
		Bullet* bullet = &game->bullets[i];

		if(bullet->position.x < 0.0f || bullet->position.x > (float) SCREEN_WIDTH
		   || bullet->position.y < 0.0f || bullet->position.y > (float)SCREEN_HEIGHT)
		{
			game->bullets[i] = game->bullets[game->bulletCount - 1];
			game->bulletCount -= 1;
		}
	}
}

int gameEnemyAliveCount(Game* game)
{
	int count = 0;
	for(int i = 0; i < ENEMY_COUNT; i++)
	{
		if(game->enemies[i].life > 0)
			count++;
	}
	return count;
}
void loadData(Game* game)
{
	game->atlas = LoadTexture("assets/mines.png");
	game->background = LoadTexture("assets/background.png");
	game->foreground = LoadTexture("assets/foreground.png");
	game->player.texture = &game->atlas;
}

void unloadData(Game* game)
{
	UnloadTexture(game->atlas);
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
}

//TODO : Collisions
void gameCollisions(Game* game)
{
	for(int i = 0; i < game->bulletCount; i++)
	{
		//Bullet* bullet = &game->bullets[i];
		for(int j = 0; j < ENEMY_COUNT; j++)
		{
			//Enemy* enemy = &game->enemies[j];

		}
	}
}

void gameIsOver(Game* game)
{
	for(int i = 0; i < ENEMY_COUNT; i++)
	{
		if(game->enemies[i].life > 0)
			return;
	}
	game->state = GS_GAMEOVER;
}

void Shutdown(Game* game)
{
	game->state = GS_CLOSE;
	unloadData(game);
	CloseWindow();
}