#include "game.h"
#include "collision.h"

static void initAllEnemies(Game *game, EnemyType type, int size)
{
	Vector2d random;

	PlayerCollisionBox player1 = getPlayerCollisionBox(game->player[0].rotation, game->player[0].position, 0.25f);
	PlayerCollisionBox player2 = getPlayerCollisionBox(game->player[1].rotation, game->player[0].position, 0.25f);
	for(int i = 0; i < game->enemyCount; i++)
	{
		FloatingCollisionBox floating;

		if (!game->twoPlayers)
		{
			do
			{
				random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
				random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
				floating = getFloatingCollisionBox(0, random, 0);
			}while (checkCollisionPlayerFloat(player1, floating));
		}
		else
		{
			do
			{
				random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
				random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
				floating = getFloatingCollisionBox(0, random, 0);
			}while (checkCollisionPlayerFloat(player1, floating) &&
					checkCollisionPlayerFloat(player2, floating));
		}
		if (i < size)
			initEnemy(&game->enemies[i], random, type, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel1(Game *game)
{
	game->layer = (MineLayer){0};
	game->mineLayerSpawned = false;
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 1;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_FLOATING, ENEMY_COUNT);
}

void initLevel2(Game *game)
{
	game->mineLayerSpawned = false;
	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 2;
	initAllEnemies(game, ET_FLOATING, 21);
	game->enemies[2].type = ET_FIREBALL;
}

void initLevel3(Game *game)
{
	game->mineLayerSpawned = false;
	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 3;
	initAllEnemies(game, ET_FLOATING, 24);
	game->enemies[2].type = ET_FIREBALL;
	game->enemies[6].type = ET_MAGNETIC_FIREBALL;
}

void initLevel4(Game *game)
{
	game->mineLayerSpawned = false;
	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 4;
	initAllEnemies(game, ET_MAGNETIC_FIREBALL, 24);
}

void initLevel5(Game *game)
{
	game->mineLayerSpawned = false;
	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 5;
	initAllEnemies(game, ET_MAGNETIC_FIREBALL, 28);
}

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
