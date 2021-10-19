#pragma once
#include <raylib.h>
#include "game.h"

#define ENEMY_TRANSFORM     Vector2 position; \
float scale;\
float rotation;\
float speed;\
int type;\
int size;\


//enemies commom base
typedef struct EnemyTranform
{
    ENEMY_TRANSFORM
} EnemyTranform;

//enemy size
enum {LOW_SIZE = 1,MEDIUM_SIZE,BIG_SIZE};

//enemy identifier
enum {FLOATING_MINE = 1, FIREBALL_MINE, MAGNETIC_MINE, MAGNETIC_FIREBALL_MINE};

//All enemies objects
typedef struct FloatingMine
{
    ENEMY_TRANSFORM
} FloatingMine;

typedef struct FireBallMine
{
    ENEMY_TRANSFORM
		bool touched; // to shoot if touched
} FireBallMine;

typedef struct MagneticMine //pursuit the player
{
    ENEMY_TRANSFORM

} MagneticMine;


typedef struct MagneticFireballMine //pursuit the player
{
    ENEMY_TRANSFORM
		bool touched; // to shoot if touched
} MagneticFireballMine;

//With these struct, we define a union enemy to simulate a OPP
typedef union Enemy
{
    int type;
    EnemyTranform enemyBase;
    FloatingMine floatingMine;
    FireBallMine fireBallMine;
    MagneticMine magneticMine;
    MagneticFireballMine magneticFireMine;

} Enemy;


//enemy Base 
void initEnemy(Enemy* enemy);
void updateEnemy(Enemy* enemy,float deltaTime);
void drawEnemy(Enemy* enemy,const Texture2D texture);
