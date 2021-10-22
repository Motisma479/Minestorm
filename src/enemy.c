#include "enemy.h"
#include <assert.h>
#include "common.h"

static Enemy defs[] = {
    {ET_FLOATING, ES_BIG, {0, 0}, {20, 20}, 0, 3, false, 100},               //0
    {ET_FLOATING, ES_MEDIUM, {0, 0}, {40, 40}, 0, 3, false, 135},            //1
    {ET_FLOATING, ES_SMALL, {0, 0}, {60, 60}, 0, 3, false, 100},             //2

    {ET_FIREBALL, ES_BIG, {0, 0}, {20, 20}, 0, 3, false, 325},               //3
    {ET_FIREBALL, ES_MEDIUM, {0, 0}, {40, 40}, 0, 3, false, 360},            //4
    {ET_FIREBALL, ES_SMALL, {0, 0}, {60, 60}, 0, 3, false, 425},             //5

    {ET_MAGNETIC, ES_BIG, {0, 0}, {20, 20}, 0, 3, false, 500},               //6
    {ET_MAGNETIC, ES_MEDIUM, {0, 0}, {40, 40}, 0, 3, false, 535},            //7
    {ET_MAGNETIC, ES_SMALL, {0, 0}, {60, 60}, 0, 3, false, 600},             //8

    {ET_MAGNETIC_FIREBALL, ES_BIG, {0, 0}, {20, 20}, 0, 3, false, 750},      //9
    {ET_MAGNETIC_FIREBALL, ES_MEDIUM,{0, 0}, {40, 40}, 0, 3, false, 585},    //10
    {ET_MAGNETIC_FIREBALL, ES_SMALL, {0, 0}, {60, 60}, 0, 3, false, 850},    //11
    //Implement new enemie here
};

Enemy getEnemieStat(int id){
    assert(id >= 0 && id < (sizeof(defs) / sizeof(defs[0])));
	return defs[id];
}

void initEnemy(Enemy* enemy, Vector2 position, int enemy_ran)
{
    *enemy = getEnemieStat(enemy_ran);

	enemy->life = MAX_ENEMY_LIFE;
	enemy->position = position;

	
	enemy->rotation = (float)GetRandomValue(0,360);
}

void updateEnemy(Enemy* enemy,float deltaTime, Player* playerI, Player* playerII )
{
	if(enemy->life <= 0.0f){ //if enemy is dead, we do not update his position
		return;
    }

	Vector2d toTargetI = subsVector2d((Vector2d){playerI->position.x,playerI->position.y},(Vector2d){enemy->position.x,enemy->position.y});
	Vector2d toTargetII = subsVector2d((Vector2d){playerII->position.x,playerII->position.y},(Vector2d){enemy->position.x,enemy->position.y});
	float distI = lengthVector2d(toTargetI);
	float distII = lengthVector2d(toTargetII);
	Vector2 *position = &enemy->position;
	Vector2 direction = {cosf(enemy->rotation*DEG2RAD),sinf(enemy->rotation*DEG2RAD)};//base 

	if (enemy->active)
	{
		if (enemy->type == ET_MAGNETIC || enemy->type == ET_MAGNETIC_FIREBALL)
		{
			if (distI <200 || distII <200)
			{
				if (distI <= distII)
				{
					enemy->position.x += (enemy->speed.x * (toTargetI.x /distI)) * deltaTime;
					enemy->position.y += (enemy->speed.y * (toTargetI.y /distI)) * deltaTime;
				}else{
					enemy->position.x += (enemy->speed.x * (toTargetII.x /distII)) * deltaTime;
					enemy->position.y += (enemy->speed.y * (toTargetII.y /distII)) * deltaTime;
				}
				
				
			}
		}else{
			position->x += (enemy->speed.x * direction.x ) * deltaTime;
			position->y += (enemy->speed.y * direction.y ) * deltaTime;
		}
	} 
	
 	if (position->x < 64.0f) { position->x = (float)SCREEN_WIDTH - 64.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 64.0f) { position->x = 64.0f; }

	if (position->y < 80.0f) { position->y = (float)SCREEN_HEIGHT - 80.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 80.0f) { position->y = 80.0f; } 

}

void drawEnemy(Enemy* enemy, const Texture2D texture)
{
	Color color = RED;
	Vector2 size;
	Rectangle textureCoord = {0};

	if (enemy->type == ET_NONE)
		return;
	if (!enemy->active)
		textureCoord = (Rectangle){345, 90, 75, 75};
	else
	{
		switch (enemy->type)
		{
			case ET_NONE: break;
			case ET_FLOATING: textureCoord = (Rectangle){70, 332, 117, 109}; break;
			case ET_FIREBALL: textureCoord = (Rectangle){846, 332, 104, 106}; break;
			case ET_MAGNETIC: textureCoord = (Rectangle){335, 332, 99, 105}; break;
			case ET_MAGNETIC_FIREBALL: textureCoord = (Rectangle){567, 308, 149, 153}; break;
		}
	}

	switch(enemy->size)
	{
		case ES_NONE:
		{
			size.x = textureCoord.width / 8;
			size.y = textureCoord.height / 8;
			color = WHITE;
		}break;
		case ES_SMALL:
		{
			size.x = textureCoord.width / 8;
			size.y = textureCoord.height / 8;
		}break;
		case ES_MEDIUM:
		{
			size.x = textureCoord.width / 4;
			size.y = textureCoord.height / 4;
		}break;
		case ES_BIG:
		{
			size.x = textureCoord.width / 2;
			size.y = textureCoord.height / 2;
		}break;
	}

	Rectangle position = {
		enemy->position.x,
		enemy->position.y,
		size.x,
		size.y};

	Vector2 center = {position.width / 2.0f, position.height / 2.0f};
	DrawTexturePro(texture, textureCoord ,position,center,enemy->rotation, color);
}
