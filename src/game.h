#pragma once
#include <raylib.h>
#include <stdbool.h>
#include "commom.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef enum
{
	GS_MENU,
	GS_PAUSE,
	GS_PLAY,
	GS_PLAY2,
	GS_GAMEOVER,
	GS_CLOSE,
} GameState;
typedef struct Game
{
	GameState state;
	Texture2D atlas;
	Texture2D foreground;
	Texture2D background;

	Rectangle bulletCoord;
	float ticksCount;

	Player player;

	Enemy enemies[ENEMY_COUNT];

	int    bulletCount;
	Bullet bullets[BULLET_CAPACITY];
} Game;

bool initGame(Game* game);
void runLoop(Game* game);
void processInput(Game* game);
void updateGame(Game* game);

void gameStats(Game* game);

int gameEnemyAliveCount(Game* game);

void gameAddBullet(Game* game, Vector2 position);
void gameRemoveBullet(Game* game);
void gameCollisions(Game* game);

void loadData(Game* game);
void unloadData(Game* game);

void gameIsOver(Game* game);
void Shutdown(Game* game);
