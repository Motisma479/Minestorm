#pragma once
#include <raylib.h>

typedef struct Bullet
{
    Vector2 position;
    float speed;
    float angle;

    Texture2D texture;
} Bullet;

void initBullet(Bullet* bullet,Vector2 position,float angle);
void updateBullet(Bullet* bullet,float deltaTime);
void drawBullet(Bullet* bullet);
void unloadBulletData(Bullet* bullet);

