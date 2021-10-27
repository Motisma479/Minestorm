#include "game.h"

void initLevel1(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 1;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_FLOATING, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel2(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 2;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_FIREBALL, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel3(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 3;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_MAGNETIC, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel4(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 4;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_MAGNETIC_FIREBALL, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel5(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 5;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_MAGNETIC_FIREBALL, ES_NONE);
		game->enemies[i].active = false;
	}
}

#include <stdio.h>

void startLevel(Game *game)
{
	switch(game->level)
	{
		case 1: initLevel1(game);break;
		case 2: initLevel2(game);break;
		case 3: initLevel3(game);break;
		case 4: initLevel4(game);break;
		case 5: initLevel5(game);break;
		default:initLevel1(game);break;
	}
	if (game->level > 5)
		game->level = 1;
}
