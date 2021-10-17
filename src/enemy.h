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
	Texture2D *texture;
	Rectangle textureCoord;
} Enemy;

void initEnemy(Texture2D *texture, Enemy* enemy);
void updateEnemy(Enemy* enemy,float deltaTime);
void drawEnemy(Enemy* enemy);

void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
