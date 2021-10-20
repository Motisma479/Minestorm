#include "bullet.h"
#include <math.h>

void initBullet(Bullet* bullet,Vector2 position,float angle)
{
    bullet->position = position;
    bullet->speed = 700.0f;
    bullet->angle = angle;
    bullet->scale = 64.0f;

    /*bullet->rectComponent.min.x = bullet->position.x - bullet->scale /2.0f;
    bullet->rectComponent.min.y = bullet->position.y - bullet->scale /2.0f;
    bullet->rectComponent.max.x = bullet->position.x + bullet->scale /2.0f;
    bullet->rectComponent.max.y = bullet->position.y + bullet->scale /2.0f;*/
}
void updateBullet(Bullet* bullet,float deltaTime)
{
    Vector2 position = bullet->position;

    position.x +=bullet->speed * cosf(bullet->angle*DEG2RAD - PI / 2.0f) * deltaTime;
    position.y += bullet->speed * sinf(bullet->angle*DEG2RAD - PI / 2.0f)* deltaTime;

    bullet->position = position;

    //update rectangle component
    //bullet->rectComponent.min.x = (bullet->position.x < bullet->rectComponent.min.x) ? bullet->position.x : bullet->rectComponent.min.x ;
    //bullet->rectComponent.min.y = (bullet->position.y < bullet->rectComponent.min.y) ? bullet->position.y : bullet->rectComponent.min.y ;
    //bullet->rectComponent.max.x = (bullet->position.x > bullet->rectComponent.max.x) ? bullet->position.x : bullet->rectComponent.max.x ;
    //bullet->rectComponent.max.y = (bullet->position.y > bullet->rectComponent.max.y) ? bullet->position.y : bullet->rectComponent.max.y ;
}

void drawBullet(Bullet* bullet,const Texture2D* texture)
{
    //Rectangle rect = {3.0f*texture->width/4.0f,0.0f,bullet->scale,bullet->scale};

    Rectangle rect = {3.0f*texture->width/4.0f,0.0f,texture->width/4.0f,texture->height/2.0f};
	Rectangle position = { bullet->position.x,bullet->position.y,bullet->scale,bullet->scale};
	Vector2 center = { bullet->scale/2.0f,bullet->scale/2.0f};
    DrawTexturePro(*texture,rect,position,center,bullet->angle,SKYBLUE);
    
}
