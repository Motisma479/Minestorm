#pragma once
#include <raylib.h>
#include "Math.h"

typedef struct Bullet
{
    Vector2 position;
    float speed;
    float angle;
    float scale;

    AABB rectComponent;

} Bullet;

void initBullet(Bullet* bullet,Vector2 position,float angle);
void updateBullet(Bullet* bullet,float deltaTime);
void drawBullet(Bullet* bullet,const Texture2D* texture);


