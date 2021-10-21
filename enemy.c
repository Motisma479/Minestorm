#include "enemy.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <raylib.h>
#include "common.h"

static Enemy defs[] = {
    {FLOATING, {0, 0}, {0, 0}, 0, 3, SZBIG, 100},               //0
    {FLOATING, {0, 0}, {0, 0}, 0, 3, SZMEDIUM, 135},          //1
    {FLOATING, {0, 0}, {0, 0}, 0, 3, SZSMALL, 100},             //2

    {FIREBALL, {0, 0}, {0, 0}, 0, 3, SZBIG, 325},               //3
    {FIREBALL, {0, 0}, {0, 0}, 0, 3, SZMEDIUM, 360},          //4
    {FIREBALL, {0, 0}, {0, 0}, 0, 3, SZSMALL, 425},             //5

    {MAGNETIC, {0, 0}, {0, 0}, 0, 3, SZBIG, 500},               //6
    {MAGNETIC, {0, 0}, {0, 0}, 0, 3, SZMEDIUM, 535},          //7
    {MAGNETIC, {0, 0}, {0, 0}, 0, 3, SZSMALL, 600},             //8

    {MAGNETIC_FIREBALL, {0, 0}, {0, 0}, 0, 3, SZBIG, 750},      //9
    {MAGNETIC_FIREBALL, {0, 0}, {0, 0}, 0, 3, SZMEDIUM, 585}, //10
    {MAGNETIC_FIREBALL, {0, 0}, {0, 0}, 0, 3, SZSMALL, 850},    //11
    //Implement new enemie here
};

void initEnemy(Enemy* enemy)
{
    
	//*enemy = getEnemieStat(GetRandomValue(0,12));
    
	enemy->position.x = GetRandomValue(0,SCREEN_WIDTH);
	enemy->position.y = GetRandomValue(0,SCREEN_HEIGHT);
    enemy->speed.x = 40;
	enemy->speed.y = 40;
	enemy->direction = GetRandomValue(0,360);
    enemy->life = MAX_ENEMY_LIFE;
    /*
	enemy->position.x = GetRandomValue(0,SCREEN_WIDTH);
	enemy->position.y = GetRandomValue(0,SCREEN_HEIGHT);
	enemy->speed.x = GetRandomValue(-20,80);
	enemy->speed.y = GetRandomValue(-20,80);
	enemy->direction = GetRandomValue(0,360);
	enemy->enemy_type = GetRandomValue(0, 3);
    */
	
}

Enemy getEnemieStat(int id){
    assert(id >= 0 && id < (sizeof(defs) / sizeof(defs[0])));
	return defs[id];
}

void updateEnemy(Enemy* enemy, float deltaTime){
    /*
    for (int i = 0; i < enemieForLevel; i++)
    {
        if(enemie[i].life <= 0.0f) //if enemy is dead, we do not update his position
		return;

	    Vector2 position = enemie[0].position;

	    position.x += enemie[i].speed.x * deltaTime;
	    position.y += enemie[i].speed.y * deltaTime;

	    if(position.x < 0.0f) position.x = (float)SCREEN_WIDTH - 1.0f;
	    else if(position.x > (float)SCREEN_WIDTH) position.x = 1.0f;

	    if(position.y < 0.0f) position.y = (float)SCREEN_HEIGHT - 1.0f;
	    else if(position.y > (float)SCREEN_HEIGHT) position.y = 1.0f;

	    enemie[i].position = position;
    }

    */
   /*
   if(enemy->life <= 0.0f) //if enemy is dead, we do not update his position
		return;

	

	position.x += enemy->speed.x * deltaTime;
	position.y += enemy->speed.y * deltaTime;

    Vector2 direction = {cosf(enemy->direction*DEG2RAD),sinf(enemy->direction*DEG2RAD)};

	if(position.x < 0.0f) position.x = (float)SCREEN_WIDTH - direction.x;
	else if(position.x > (float)SCREEN_WIDTH) position.x = direction.x;

	if(position.y < 0.0f) position.y = (float)SCREEN_HEIGHT - direction.y * (enemy->speed);
	else if(position.y > (float)SCREEN_HEIGHT) position.y = direction.y;

	*/
    

    //Movement
    Vector2 position = enemy->position;

	Vector2 direction = {cosf(enemy->direction*DEG2RAD),sinf(enemy->direction*DEG2RAD)};

	position.x += (enemy->speed.x * direction.x ) * deltaTime;
	position.y += (direction.y * enemy->speed.y) * deltaTime;

	// Wraparound
	if (position.x < 0.0f) { position.x = (float)SCREEN_WIDTH - 1.0f; }
	else if (position.x > (float)SCREEN_WIDTH ) { position.x = 1.0f; }

	if (position.y < 0.0f) { position.y = (float)SCREEN_HEIGHT - 1.0f; }
	else if (position.y > (float)SCREEN_HEIGHT ) { position.y = 1.0f; }

    enemy->position = position;
}


void drawEnemy(Enemy* enemy, Texture2D texture){
    
    int frameWidth = texture.width/4;
    int frameHeight = texture.height/2;

    
    Rectangle sourceRec = { frameWidth*0, frameHeight*1, (float)frameWidth, (float)frameHeight };
    

    /*
    
    for (int i = 0; i<enemieForLevel;i++)
    {
        Rectangle destRec = { enemy[i].position.x*5, enemy[i].position.y*5, frameWidth*0.5f, frameHeight*0.5f };
        Vector2 position = { enemy[i].position.x, enemy[i].position.y };
        Vector2 center = { frameWidth*0.5f*0.5f, frameHeight*0.5f*0.5f };
        //DrawTexturePro(texture,sourceRec,destRec,position,enemy[i].direction,RED);
        DrawTexturePro(texture,sourceRec,destRec,center,enemy[i].direction,RED);

    }
    */
    Rectangle destRec = { enemy->position.x, enemy->position.y, frameWidth*0.5f, frameHeight*0.5f };
    
	Vector2 center = { frameWidth/2.0f, frameHeight/2.0f };
	DrawTexturePro(texture, sourceRec,destRec,center,enemy->direction,RED);

    
}
