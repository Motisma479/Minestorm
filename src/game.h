#pragma once
#include <raylib.h>
#include <stdbool.h>
#include "common.h"
#include "mineLayer.h"
#include "enemy.h"
#include "bullet.h"
#include "Math.h"

typedef enum
{
	GS_MENU,
	GS_PAUSE,
	GS_PLAY,
	GS_GAMEOVER,
	GS_CLOSE,
} GameState;

typedef enum PlayerAction
{
	PA_ACCELERATION = 1UL,
	PA_TURN_LEFT    = 1UL << 1,
	PA_TURN_RIGHT   = 1UL << 2,
	PA_TELEPORT     = 1UL << 3,
	PA_SHOOT        = 1UL << 4,
} PlayerAction;

typedef struct Player
{
	Bullet       bullets[BULLET_CAPACITY];
	int          bulletCount;
    Vector2      position;
	Vector2      acceleration;
    float        rotation;
	int          lives;
	int          score;
	PlayerAction action;
	Rectangle    textureCoord;
} Player;

typedef struct Game
{
	GameState state;
	Texture2D atlas;
	Texture2D foreground;
	Texture2D background;

	Rectangle bulletCoord;
	float     ticksCount;

	Player    player[2];
	MineLayer layer;
	int       enemyCount;
	Enemy     enemies[ENEMY_COUNT];
	int       level;
	bool      levelStart;
	char      drawCollisions;
	int       framesCounter;
	bool      twoPlayers;
} Game;

bool initGame(Game* game);
void runGameLoop(Game* game);
void processInput(Game* game);
void updateGame(Game* game);

int gameEnemyAliveCount(Game* game);

void gameAddBullet(Player *player);
void gameRemoveBullet(Player *player);
void gameCollisions(Game* game, Player *player);

void loadData(Game* game);
void unloadData(Game* game);

void gameIsOver(Game* game);
void Shutdown(Game* game);


bool initGame(Game* game);
void processInput(Game* game);
void updateGame(Game* game);
void runGameLoop(Game* game);
void shutdown(Game* game);

void addEnemyToGame();

void pauseGame(Game* game);
void drawGameBackground(Game* game);
void loadGameData(Game* game);
void unloadGameData(Game* game);
