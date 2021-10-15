#include "bullet.h"
#include <math.h>

void initBullet(Bullet* bullet,Vector2 position,float angle)
{
    bullet->position = position;
    bullet->texture = LoadTexture("assets/mines.png");
    bullet->speed = 700.0f;
    bullet->angle = angle;
}
void updateBullet(Bullet* bullet,float deltaTime)
{
    Vector2 position = bullet->position;

    position.x +=bullet->speed * cosf(bullet->angle*DEG2RAD) * deltaTime;
    position.y += bullet->speed * sinf(bullet->angle*DEG2RAD)* deltaTime;

    bullet->position = position;
}

void drawBullet(Bullet* bullet)
{
    //DrawTexture(bullet->texture,bullet->position.x,bullet->position.y,WHITE);

    Rectangle rect = {0,0,12,128};
    Rectangle position = {bullet->position.x,bullet->position.y,64,64};

    Vector2 center = {bullet->texture.width / 2.0f,bullet->texture.height / 2.0f};
    DrawTexturePro(bullet->texture,rect,position,center,bullet->angle,WHITE);


}

void unloadBulletData(Bullet* bullet)
{
    UnloadTexture(bullet->texture);
}