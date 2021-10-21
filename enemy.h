#pragma once
#include "src_Math.h"
#include <raylib.h>

typedef enum SIZE
{
    SZBIG,
    SZMEDIUM,
    SZSMALL,
}SIZE;

typedef enum SPEED
{
    SPFAST,
    SPMEDIUM,
    SPSLOW,
}SPEED;

typedef enum TYPE
{
    FLOATING,
    FIREBALL,
    MAGNETIC,
    MAGNETIC_FIREBALL
}TYPE;

typedef struct Enemy
{
    TYPE enemy_type;

    Vector2 position;

	Vector2 speed;

    float direction;

    int life;

    SIZE size;
    int pointsToDeliver;
}Enemy;

void updateEnemy(Enemy* enemie, float deltaTime);
void drawEnemy(Enemy* enemie, Texture2D texture);
Enemy getEnemieStat(int id);