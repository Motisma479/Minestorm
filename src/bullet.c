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

void drawBullet(Bullet* bullet, const Texture2D texture)
{
	//DrawTexture(bullet->texture,bullet->position.x,bullet->position.y,WHITE);
	Rectangle rect     = {885, 116, 25, 25};
	Rectangle position = {bullet->position.x,bullet->position.y , rect.width / 2, rect.height / 2};
	Vector2 origin     = {rect.width / 2, rect.height / 2};

	DrawTexturePro(texture,rect,position,origin,bullet->angle, YELLOW);
}
