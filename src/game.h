#pragma once
#include <raylib.h>
#include "player.h"
#include "mineLayer.h"
#include "enemy.h"
#include "commom.h"

typedef struct Game
{
	bool gameIsRunning;
	bool gamePaused;

	Texture2D background;
	Texture2D foreground;
	Texture2D gameTexture;

	Player player;
	MineLayer layer;

	int enemiesCount;
	//Enemy enemies[ENEMY_CAPACITY];
} Game;

bool initGame(Game* game);
void processInput(Game* game);
void updateGame(Game* game);
void runGameLoop(Game* game);
void drawGame(Game* game);
void shutdown(Game* game);

void addEnemyToGame();

void pauseGame(Game* game);
void drawGameBackground(Game* game);
void loadGameData(Game* game);
void unloadGameData(Game* game);