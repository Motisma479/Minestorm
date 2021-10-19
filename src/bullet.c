#include "bullet.h"
#include <math.h>

void initBullet(Bullet* bullet,Vector2 position,float angle)
{
	bullet->position = position;
	bullet->speed    = 700.0f;
	bullet->angle    = angle;
}
void updateBullet(Bullet* bullet,float deltaTime)
{
	Vector2 *position = &bullet->position;

	position->x += bullet->speed * cosf(bullet->angle*DEG2RAD) * deltaTime;
	position->y += bullet->speed * sinf(bullet->angle*DEG2RAD) * deltaTime;
}

void drawBullet(Bullet* bullet, const Texture2D texture, Color color)
{
	Rectangle rect     = {885, 116, 25, 25};
	Rectangle position = {bullet->position.x,bullet->position.y , rect.width / 4, rect.height / 4};
	Vector2 origin     = {position.width / 2, position.height / 2};

	DrawTexturePro(texture,rect,position,origin, 0, color);
}
