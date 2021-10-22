#pragma once
#include "Math.h"
#include "player.h"
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
} EnemyType;

typedef struct Enemy
{
    EnemyType type;
	EnemySize size;

	Vector2   position;
	Vector2   speed;

	float     rotation;
	int       life;

	bool      active;

    int pointsToDeliver;
} Enemy;

void initEnemy(Enemy* enemy, Vector2 position, int enemy_ran);
void makeEnemyType(Enemy* enemy, EnemyType type);
void updateEnemy(Enemy* enemy,float deltaTime, Player* playerI, Player* playerII);
void drawEnemy(Enemy* enemy, const Texture2D texture);
void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
