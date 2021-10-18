#include "enemy.h"


void initEnemy(Enemy* enemy)
{
    
    for(int i = 0; i < ENEMY_CAPACITY; i++)
    {
        //Enemy enemy = {0};
        switch (enemy->type)
        {
        case FLOATING_MINE:
            initFloatingMine(&enemy->floatingMine);
            break;
        case MAGNETIC_MINE:
            break;
        case FIREBALL_MINE:
            break;
        case MAGNETIC_FIREBALL_MINE:
            break;
        default:
            break;
        }
    }

}
void updateEnemy(Enemy* enemy,float deltaTime)
{
    switch (enemy->type)
    {
    case FLOATING_MINE:
        updateFloatingMine(&enemy->floatingMine,deltaTime);
        break;
    case MAGNETIC_MINE:
        break;
    case FIREBALL_MINE:
        break;
    case MAGNETIC_FIREBALL_MINE:
        break;
    default:
        break;

    }
}
void drawEnemy(Enemy* enemy,const Texture2D texture)
{
    switch (enemy->type)
    {
    case FLOATING_MINE:
        drawFloatingMine(&enemy->floatingMine,texture);
        break;
    case MAGNETIC_MINE:
        break;
    case FIREBALL_MINE:
        break;
    case MAGNETIC_FIREBALL_MINE:
        break;
    default:
        break;

    }
}

void initFloatingMine(FloatingMine* mine)
{
    mine->position = (Vector2){ (float)GetRandomValue(64,SCREEN_WIDTH - 64),
		(float)GetRandomValue(80,SCREEN_HEIGHT - 80) };
    mine->scale = 128.0f;
    mine->rotation = 0.0f;
    mine->speed = GetRandomValue(-20,80) / 1.0f;
    mine->size = GetRandomValue(0,1) == 1 ? LOW_SIZE :(GetRandomValue(2,3) == 2 ? MEDIUM_SIZE : BIG_SIZE);
    mine->type = FLOATING_MINE;
}
void updateFloatingMine(FloatingMine* mine,float deltaTime)
{
    Vector2 position = mine->position;

    position.x += mine->speed * deltaTime;
    position.y += mine->speed * deltaTime;

    if (position.x < 64.0f) { position.x = (float)SCREEN_WIDTH - 64.0f; }
    else if (position.x > (float)SCREEN_WIDTH - 64.0f) { position.x = 64.0f; }

    if (position.y < 80.0f) { position.y = (float)SCREEN_HEIGHT - 80.0f; }
    else if (position.y > (float)SCREEN_HEIGHT - 80.0f) { position.y = 80.0f; }

    mine->position = position;
}
void drawFloatingMine(FloatingMine* mine,const Texture2D texture)
{
    Rectangle rect = { 0.0f,128.0f,texture.width / 4.0f,texture.height / 2.0f };
    Rectangle position = { mine->position.x,mine->position.y,mine->scale,mine->scale};
    Vector2 center = { mine->scale / 2.0f,mine->scale / 2.0f };

    DrawTexturePro(texture, rect, position, center, mine->rotation, RED);
}