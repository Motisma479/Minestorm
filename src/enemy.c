#include "enemy.h"
#include "common.h"
#include "Math.h"
#include "game.h"

static Enemy defs[] = {
	{{0, 0}, {0, 0}, 0, false, false,  ET_FLOATING, ES_NONE, 0.125f, 0, 100},
	{{0, 0}, {20, 20}, 0, false, false,  ET_FLOATING, ES_BIG, 0.5f, 0, 100},                  //0
    {{0, 0}, {40, 40}, 0, false , false, ET_FLOATING, ES_MEDIUM, 0.25f, false, 135},          //1
    {{0, 0}, {60, 60}, 0, false , false, ET_FLOATING, ES_SMALL, 0.125f, false, 100},          //2

    {{0, 0}, {20, 20}, 0, false , false, ET_FIREBALL, ES_BIG, 0.5f, false, 325},              //3
    {{0, 0}, {40, 40}, 0, false , false, ET_FIREBALL, ES_MEDIUM, 0.25f, false, 360},          //4
    {{0, 0}, {60, 60}, 0, false , false, ET_FIREBALL, ES_SMALL, 0.125f, false, 425},          //5

    {{0, 0}, {20, 20}, 0, false , false, ET_MAGNETIC, ES_BIG, 0.5f, false, 500},              //6
    {{0, 0}, {40, 40}, 0, false , false, ET_MAGNETIC, ES_MEDIUM, 0.25f, false, 535},          //7
    {{0, 0}, {60, 60}, 0, false , false, ET_MAGNETIC, ES_SMALL, 0.125f, false, 600},          //8

	{{0, 0}, {20, 20}, 0, false , false, ET_MAGNETIC_FIREBALL, ES_BIG, 0.5f, false, 750},     //9
    {{0, 0}, {40, 40}, 0, false , false, ET_MAGNETIC_FIREBALL, ES_MEDIUM, 0.25f, false, 585}, //10
    {{0, 0}, {60, 60}, 0, false , false, ET_MAGNETIC_FIREBALL, ES_SMALL, 0.125f, false, 850}, //11

	{{0, 0}, {200, 200},0, false, false,  ET_MINE_LAYER, ES_BIG, 0.5f, false, 850},           //12
};

Enemy getEnemieStat(EnemyType type, EnemySize size){
	for (int i = 0; i < (int)(sizeof(defs) / sizeof(defs[0]));i++)
	{
		if (defs[i].type == type && defs[i].size == size)
			return (defs[i]);
	}
	return (defs[0]);
}

void initEnemy(Enemy* enemy, Vector2d position, EnemyType type, EnemySize size)
{
	*enemy = getEnemieStat(type, size);
	enemy->position = position;
	float random = GetRandomValue(0, 1250);
	random /= 1000.0f;
	enemy->lastShot = random;
}

void updateEnemy(Game *game, Enemy* enemy,float deltaTime, Player *player1, Player *player2)
{
	Vector2d *position = &enemy->position;

	if (enemy->active)
	{
		switch(enemy->type)
		{
			case ET_FIREBALL:
			case ET_FLOATING:
			{
				position->x += enemy->speed.x * deltaTime;
				position->y += enemy->speed.y * deltaTime;
			}break;
			case ET_MAGNETIC_FIREBALL:
			case ET_MAGNETIC:
			{
				Vector2d centerEnemy =
					subsVector2d((Vector2d){SCREEN_WIDTH / 2,
									 SCREEN_HEIGHT / 2}, *position);

				Vector2d playerPos =
				(Vector2d){(int)(centerEnemy.x + player1->position.x) % SCREEN_WIDTH,
					(int)(centerEnemy.y + player1->position.y) % SCREEN_HEIGHT};

				Vector2d towardsPlayer =
					subsVector2d(playerPos, (Vector2d){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

				playerPos = normalizeVector2d(towardsPlayer);

				position->x += (enemy->speed.x * deltaTime * playerPos.x);
				position->y += (enemy->speed.y * deltaTime * playerPos.y);
			}break;
			case ET_MINE_LAYER:
			{
				if ((int)position->x < (int)(SCREEN_WIDTH / 2) - 10 ||
					(int)position->x > (int)(SCREEN_WIDTH / 2) + 10)
					position->x += (enemy->speed.x * deltaTime);
				else if ((int)position->y < (int)(SCREEN_HEIGHT - 81))
					position->y += (enemy->speed.y * deltaTime);
				else
				{
					enemy->type = ET_NONE;
					enemy->active = false;
				}
			}break;
			default:;
		}
		switch(enemy->type)
		{
			case ET_FIREBALL:
			case ET_MAGNETIC_FIREBALL:
			{
				if (enemy->lastShot < 0.01f)
					gameAddBullet(game, BS_ENEMY, enemy);
			}break;
			default:;
		}
		enemy->lastShot += deltaTime;
		if (enemy->lastShot > 6.0f)
			enemy->lastShot = 0.0f;

	}

	if (position->x < 64.0f) { position->x = (float)SCREEN_WIDTH - 64.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 64.0f) { position->x = 64.0f; }

	if (position->y < 80.0f) { position->y = (float)SCREEN_HEIGHT - 80.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 80.0f) { position->y = 80.0f; }

}

void drawEnemy(Enemy* enemy, const Texture2D texture)
{
	Color color = RED;
	Rectangle textureCoord = {0};
	Rectangle position = {0};


	if (enemy->type == ET_NONE)
		return;

	float scale = 1.0f;
	switch(enemy->size)
	{
		case ES_NONE:
		{
			scale = 0.125f;
			color = WHITE;
		}break;
		case ES_SMALL: scale = 0.125f;break;
		case ES_MEDIUM:scale = 0.25f;break;
		case ES_BIG:   scale = 0.5f;break;
	}

	position.x = enemy->position.x;
	position.y = enemy->position.y;
	if (!enemy->active)
		textureCoord = (Rectangle){345, 90, 75, 75};
	else
	{
		switch (enemy->type)
		{
			case ET_NONE: break;

			case ET_FLOATING: 
			{
				textureCoord = (Rectangle){70, 332, 117, 109};
				position.x = enemy->position.x - (9 * scale);
				position.y = enemy->position.y - (58 * scale);
			} break;

			case ET_FIREBALL: {
				textureCoord = (Rectangle){846, 332, 104, 106};
				position.x = enemy->position.x - (14 * scale);
				position.y = enemy->position.y - (12 * scale);
			}break;

			case ET_MAGNETIC: 
			{
				textureCoord = (Rectangle){335, 332, 99, 105}; 
				position.x = enemy->position.x + (68 * scale);
				position.y = enemy->position.y + (65 * scale);
			}
			break;

			case ET_MAGNETIC_FIREBALL: textureCoord = (Rectangle){567, 308, 149, 153}; break;
			case ET_MINE_LAYER: textureCoord = (Rectangle){513, 89, 255, 78}; break;
		}
	}

	position.width  = textureCoord.width  * scale;
	position.height = textureCoord.height * scale;
	Vector2 center = {position.width / 2.0f, position.height / 2.0f};
	if (enemy->hit)
		color = WHITE;
	DrawTexturePro(texture, textureCoord ,position, center, enemy->rotation, color);
}
