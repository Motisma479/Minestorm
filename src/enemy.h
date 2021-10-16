#pragma once
#include <raylib.h>

typedef struct Enemy
{
    Vector2 position;
    Vector2 speed;
    float rotation;
    int life;

	Texture2D *texture;
	Rectangle textureCoord[4];
} Enemy;

void initEnemy(Texture2D *texture, Enemy* enemy);
void updateEnemy(Enemy* enemy,float deltaTime);
void drawEnemy(Enemy* enemy);

void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
