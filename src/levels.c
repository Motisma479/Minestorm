#include "game.h"
#include "collision.h"
#include "player.h"

void initAllEnemies(Game *game, EnemyType type, int size)
{
	Vector2d random;

	for(int i = 0; i < game->enemyCount; i++)
	{
		random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 300);
		if (i < size)
			initEnemy(&game->enemies[i], random, type, ES_NONE);
		game->enemies[i].active = false;
	}
}

void initLevel1(Game *game)
{
	game->enemyCount = ENEMY_COUNT;
	game->level = 1;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_FLOATING, 14);
	addEnemy(game, ES_BIG, ET_FLOATING);
	addEnemy(game, ES_BIG, ET_FLOATING);
}

void initLevel2(Game *game)
{
	game->enemyCount = ENEMY_COUNT;
	game->level = 2;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_FLOATING, 14);
	addEnemy(game, ES_BIG, ET_FLOATING);
	addEnemy(game, ES_BIG, ET_FIREBALL);
}

void initLevel3(Game *game)
{
	game->enemyCount = ENEMY_COUNT;
	game->level = 3;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_FLOATING, 21);
	addEnemy(game, ES_BIG, ET_FLOATING);
	addEnemy(game, ES_BIG, ET_MAGNETIC);
	addEnemy(game, ES_BIG, ET_FIREBALL);
}

void initLevel4(Game *game)
{
	game->enemyCount = ENEMY_COUNT;
	game->level = 4;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_FLOATING, 21);
	addEnemy(game, ES_BIG, ET_FLOATING);
	addEnemy(game, ES_BIG, ET_MAGNETIC_FIREBALL);
	addEnemy(game, ES_BIG, ET_FIREBALL);
}

void initLevel5(Game *game)
{
	game->enemyCount = ENEMY_COUNT;
	game->level = 5;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[i] = (Bullet){0};
	initAllEnemies(game, ET_MAGNETIC_FIREBALL, 28);
	addEnemy(game, ES_BIG, ET_FLOATING);
	addEnemy(game, ES_BIG, ET_FIREBALL);
	addEnemy(game, ES_BIG, ET_MAGNETIC_FIREBALL);
	addEnemy(game, ES_BIG, ET_MAGNETIC_FIREBALL);
}

void startLevel(Game *game)
{
	game->player[0].position = (Vector2d){SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT - 200};
	game->player[1].position = (Vector2d){SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT - 200};
	game->mineLayerSpawned = false;
	for(int i = 0; i < game->bulletCount; i++)
		game->bullets[0] = (Bullet){0};
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
