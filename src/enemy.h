#pragma once
#include <raylib.h>

typedef enum EnemyType
{
	ET_FLOATING,
	ET_FIREBALL,
	ET_MAGNETIC,
	ET_MAGNETIC_FIREBALL,
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
