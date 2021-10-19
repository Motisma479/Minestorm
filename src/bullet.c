#include "bullet.h"
#include <math.h>

void initBullet(Bullet* bullet,Vector2 position,float angle)
{
    bullet->position = position;
    bullet->speed = 700.0f;
    bullet->angle = angle;
}
void updateBullet(Bullet* bullet,float deltaTime)
{
    Vector2 position = bullet->position;

    position.x +=bullet->speed * cosf(bullet->angle*DEG2RAD - PI / 2.0f) * deltaTime;
    position.y += bullet->speed * sinf(bullet->angle*DEG2RAD - PI / 2.0f)* deltaTime;

    bullet->position = position;
}

void drawBullet(Bullet* bullet,const Texture2D* texture)
{
    float bulletSize = 128.0f;
    Rectangle rect = {3.0f*texture->width/4.0f,0.0f,texture->width/4.0f,texture->height/2.0f};
	Rectangle position = { bullet->position.x,bullet->position.y,bulletSize,bulletSize};
	Vector2 center = { bulletSize/2.0f,bulletSize/2.0f};
    DrawTexturePro(*texture,rect,position,center,bullet->angle,SKYBLUE);

}
