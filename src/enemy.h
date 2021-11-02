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
	int bulletCount;
	Bullet bullets[10];
	
} Enemy;

void initEnemy(Enemy* enemy, Vector2 position, int enemy_ran);
void makeEnemyType(Enemy* enemy, EnemyType type);
void updateEnemy(Enemy* enemy,float deltaTime, Player* playerI, Player* playerII);
void drawEnemy(Enemy* enemy, const Texture2D texture);
void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);

void initBulletEnemy(Bullet* bullet,Vector2 position,float angle);
void addBulletEnemy(Enemy *enemy);
void updateBulletEnemy(Bullet* bullet,float deltaTime);
void drawBulletEnemy(Bullet* bullet, const Texture2D texture, Color color);