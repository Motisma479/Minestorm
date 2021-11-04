#include <raylib.h>
#include "bullet.h"
#include <math.h>
#include "common.h"

void initBullet(Bullet* bullet,Vector2d position,
				float angle, BulletSource source, float speed)
{
	bullet->position = position;
	bullet->speed    = speed;
	bullet->angle    = angle;
	bullet->source   = source;
}
void updateBullet(Bullet* bullet,float deltaTime)
{
	Vector2d *position = &bullet->position;

	float xDeplacement = bullet->speed * cosf(bullet->angle*DEG2RAD) * deltaTime;
	float yDeplacement = bullet->speed * sinf(bullet->angle*DEG2RAD) * deltaTime;
	position->x += xDeplacement;
	position->y += yDeplacement;
	bullet->lifeTime += deltaTime;
	if (position->x < 10.0f) { position->x = (float)SCREEN_WIDTH - 10.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 10.0f) { position->x = 10.0f; }

	if (position->y < 10.0f) { position->y = (float)SCREEN_HEIGHT - 10.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 10.0f) { position->y = 10.0f; }
}

void drawBullet(Bullet* bullet, const Texture2D* texture, Color color)
{
	Rectangle rect     = {885, 116, 25, 25};
	Rectangle position = {bullet->position.x,bullet->position.y ,
		rect.width / 4, rect.height / 4};
	Vector2 origin     = {position.width / 2, position.height / 2};

	DrawTexturePro(*texture,rect,position,origin, 0, color);
}
