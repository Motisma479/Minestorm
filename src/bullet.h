#pragma once
#include <raylib.h>

typedef struct Bullet
{
	Vector2 position;
	float lifeTime;
	float speed;
	float angle;
} Bullet;

void initBullet(Bullet* bullet,Vector2 position,float angle);
void updateBullet(Bullet* bullet,float deltaTime);
void unloadBulletData(Bullet* bullet);
