#pragma once
#include <raylib.h>

typedef enum EnemyType
{
	ET_MINE1,
	ET_MINE2,
	ET_MINE3,
	ET_MINE4,
} EnemyType;

typedef struct Enemy
{
	Vector2 position;
	Vector2 speed;
	float rotation;
	int life;

	EnemyType type;
	Rectangle textureCoord;
} Enemy;

void initEnemy(Enemy* enemy);
void updateEnemy(Enemy* enemy,float deltaTime);
void drawEnemy(Enemy* enemy, const Texture2D texture);

void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
