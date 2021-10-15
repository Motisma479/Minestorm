#pragma once
#include <raylib.h>
#include <stdbool.h>
#include "commom.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef struct Game
{
    bool gameIsRunning;
    bool gamePaused;
    float ticksCount;

    Player player;

    Enemy enemies[ENEMY_COUNT];

    int bulletCount;
    Bullet bullets[BULLET_CAPACITY];
    
} Game;

bool initGame(Game* game);
void runLoop(Game* game);
void processInput(Game* game);
void updteGame(Game* game);
void drawGame(Game* game);

void gameStats(Game* game);

int gameEnemyAliveCount(Game* game);

void gameAddBullet(Game* game, Vector2 position);
void gameRemoveBullet(Game* game);
void gameCollisions(Game* game);

void loadData(Game* game);
void unloadData(Game* game);

void gameIsOver(Game* game);
void Shutdown(Game* game);
