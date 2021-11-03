#pragma once
#include "Math.h"
#include <raylib.h>

typedef enum EnemySize
{
	ES_NONE,
	ES_SMALL,
	ES_MEDIUM,
	ES_BIG
} EnemySize;

typedef enum EnemyType
{
	ET_NONE,
	ET_FLOATING,
	ET_FIREBALL,
	ET_MAGNETIC,
	ET_MAGNETIC_FIREBALL,
	ET_MINE_LAYER,
} EnemyType;

typedef struct Enemy
{
	Vector2d  position;
	Vector2d  speed;
	float     rotation;
	bool      active;
	bool      hit;
	EnemyType type;
	EnemySize size;
	float     scale;
	bool      shot;
	float     lastShot;
	int       pointsToRecieve;
} Enemy;

void initEnemy(Enemy* enemy, Vector2d position, EnemyType type, EnemySize size);
void makeEnemyType(Enemy* enemy, EnemyType type);
void drawEnemy(Enemy* enemy, const Texture2D texture);
void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
