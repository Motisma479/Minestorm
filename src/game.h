#pragma once
#include <raylib.h>
#include <stdbool.h>
#include "common.h"
#include "mineLayer.h"
#include "bullet.h"
#include "Math.h"
#include "enemy.h"


typedef unsigned long long int u64;

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

typedef enum DrawState
{
	DS_DEFAULT,
	DS_EVERYTHING,
	DS_COLLISIONS,
} DrawState;

typedef struct Player
{
	Vector2d     position;
	Vector2d     speed;
	Vector2d     acceleration;
    float        rotation;
	char         lives;
	u64          score;
	PlayerAction action;
	Rectangle    textureCoord;
} Player;

typedef struct Game
{
	Texture2D atlas;
	Texture2D foreground;
	Texture2D background;
	GameState state;
	Player    player[2];
	MineLayer layer;
	u64       highScore;
	int       enemyCount;
	int       bulletCount;
	Bullet    bullets[BULLET_CAPACITY];
	Enemy     enemies[ENEMY_COUNT];
	int       level;
	int       framesCounter;
	float     ticksCount;
	float     slowDown;
	DrawState draw;
	Sound     music;
	Sound     levelIntro;
	bool      mineLayerSpawned;
	bool      mineLayerUpdated;
	bool      twoPlayers;
	bool      levelStart;
	bool      bulletShot;
	bool      entityDestroyed;
} Game;

bool initGame(Game* game);
void runGameLoop(Game* game);
void processInput(Game* game);
void updateGame(Game* game);
void updateEnemy(Game *game, Enemy* enemy,float deltaTime, Player *player1, Player *player2);

int gameEnemyAliveCount(Game* game);

void gameAddBullet(Game *game, BulletSource source, Enemy *enemy);
void gameRemoveBullet(Game *game);
void gameCollisions(Game* game);
void gameIsOver(Game* game);

bool initGame(Game* game);
void processInput(Game* game);
void updateGame(Game* game);
void runGameLoop(Game* game);
void shutdown(Game* game);

int  addEnemy(Game *game, EnemySize size, EnemyType type);

