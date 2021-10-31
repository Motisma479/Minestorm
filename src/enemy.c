#include "enemy.h"
#include "common.h"
#include "Math.h"
#include "game.h"

void initEnemy(Enemy* enemy, Vector2d position, EnemyType type, EnemySize size)
{
	enemy->position = position;

	enemy->speed.x = GetRandomValue(-100, 100);
	enemy->speed.y = GetRandomValue(-100, 100);
	Vector2d normalized = normalizeVector2d(enemy->speed);
	switch (enemy->type)
	{
		case ET_FIREBALL:
		case ET_FLOATING:
		{
			switch(size)
			{
				case ES_SMALL:
				{
					enemy->speed.x = normalized.x * 60;
					enemy->speed.y = normalized.y * 60;
					enemy->scale = 0.125f;
				}break;
				case ES_MEDIUM:
				{
					enemy->speed.x = normalized.x * 40;
					enemy->speed.y = normalized.y * 40;
					enemy->scale = 0.25f;
				}break;
				case ES_BIG:
				{
					enemy->speed.x = normalized.x * 20;
					enemy->speed.y = normalized.y * 20;
					enemy->scale = 0.5f;
				}break;
				default:
				{
					enemy->speed.x = 0;
					enemy->speed.y = 0;
				}
			}
		}break;
		case ET_MAGNETIC_FIREBALL:
		case ET_MAGNETIC:
		{
			switch(size)
			{
				case ES_SMALL:
				{
					enemy->speed.x = 60;
					enemy->speed.y = 60;
					enemy->scale = 0.125f;
				}break;
				case ES_MEDIUM:
				{
					enemy->speed.x = 40;
					enemy->speed.y = 40;
					enemy->scale = 0.25f;
				}break;
				case ES_BIG:
				{
					enemy->speed.x = 20;
					enemy->speed.y = 20;
					enemy->scale = 0.5f;
				}break;
				default:
				{
					enemy->speed.x = 0;
					enemy->speed.y = 0;
				}
			}
		}break;
		default:
		{
			enemy->speed.x = 0;
			enemy->speed.y = 0;
		}
	}
	enemy->type = type;
	enemy->size = size;
	enemy->rotation = atan(normalized.y / normalized.x);
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
				Vector2d playerPos = subsVector2d(player1->position, *position);
				playerPos = normalizeVector2d(playerPos);
				float lengthInv = 1 / (lengthSqVector2d(playerPos));
				position->x += (enemy->speed.x * deltaTime * playerPos.x * lengthInv);
				position->y += (enemy->speed.y * deltaTime * playerPos.y * lengthInv);
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
