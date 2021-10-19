#include "enemy.h"
#include "common.h"

void initEnemy(Enemy* enemy)
{
	enemy->life = MAX_ENEMY_LIFE;
	enemy->position.x = GetRandomValue(0,SCREEN_WIDTH);
	enemy->position.y = GetRandomValue(0,SCREEN_HEIGHT);
	enemy->speed.x = GetRandomValue(-20,80);
	enemy->speed.y = GetRandomValue(-20,80);
	enemy->rotation = GetRandomValue(0,360);
	enemy->type = GetRandomValue(0, 3);

	switch (enemy->type)
	{
		case ET_MINE1: enemy->textureCoord = (Rectangle){70, 332, 117, 109}; break;
		case ET_MINE2: enemy->textureCoord = (Rectangle){335, 332, 99, 105}; break;
		case ET_MINE3: enemy->textureCoord = (Rectangle){567, 308, 149, 153}; break;
		case ET_MINE4: enemy->textureCoord = (Rectangle){846, 332, 104, 106}; break;
	}
}

void updateEnemy(Enemy* enemy,float deltaTime)
{
	if(enemy->life <= 0.0f) //if enemy is dead, we do not update his position
		return;

	Vector2 position = enemy->position;

	position.x += enemy->speed.x * deltaTime;
	position.y += enemy->speed.y * deltaTime;

	if(position.x < 0.0f) position.x = (float)SCREEN_WIDTH - 1.0f;
	else if(position.x > (float)SCREEN_WIDTH) position.x = 1.0f;

	if(position.y < 0.0f) position.y = (float)SCREEN_HEIGHT - 1.0f;
	else if(position.y > (float)SCREEN_HEIGHT) position.y = 1.0f;

	enemy->position = position;
}

void drawEnemy(Enemy* enemy, const Texture2D texture)
{
	Rectangle position = {
		enemy->position.x,
		enemy->position.y,
		enemy->textureCoord.width / 4,
		enemy->textureCoord.height / 4};

	Vector2 center = {position.width / 2.0f, position.height / 2.0f};
	DrawTexturePro(texture, enemy->textureCoord ,position,center,enemy->rotation,RED);
}
