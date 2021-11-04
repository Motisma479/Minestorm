#pragma once

#include "Math.h"

typedef enum BulletSource
{
	BS_PLAYER1,
	BS_PLAYER2,
	BS_ENEMY,
} BulletSource;

typedef struct Bullet
{
	Vector2d     position;
	float        lifeTime;
	float        speed;
	float        angle;
	BulletSource source;
} Bullet;

void initBullet(Bullet* bullet,Vector2d position,float angle, BulletSource source, float speed);
void updateBullet(Bullet* bullet,float deltaTime);
void unloadBulletData(Bullet* bullet);
