#include "enemy.h"
#include "commom.h"

void initEnemy(Enemy* enemy)
{
    enemy->life = MAX_ENEMY_LIFE;
    enemy->position.x = GetRandomValue(0,SCREEN_WIDTH);
    enemy->position.y = GetRandomValue(0,SCREEN_HEIGHT);
    enemy->speed.x = GetRandomValue(-20,80);
    enemy->speed.y = GetRandomValue(-20,80);
    enemy->rotation = GetRandomValue(0,360);

    loadEnemyData(enemy);
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
void drawEnemy(Enemy* enemy)
{
    Rectangle rect = {256,512,32,32};
    Rectangle position = {enemy->position.x,enemy->position.y,64,64};

    Vector2 center = {enemy->texture.width / 2.0f,enemy->texture.height / 2.0f};
    DrawTexturePro(enemy->texture,rect,position,center,enemy->rotation,WHITE);
}
void loadEnemyData(Enemy* enemy)
{
    enemy->texture = LoadTexture("assets/mines.png");
}
void unLoadEnemyData(Enemy* enemy)
{
    UnloadTexture(enemy->texture);
}