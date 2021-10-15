#include "player.h"
#include "commom.h"
#include <math.h>

void initPlayer(Player* player)
{
    player->position.x = SCREEN_WIDTH / 2.0f;
    player->position.y = SCREEN_HEIGHT / 2.0f;
    player->speed = 200.0f;
    player->rotation = 90.0f;
    player->moving = false;
    player->turnRight = false;
    player->turnLeft = false;
   
    loadPlayerData(player);
}
void inputPlayer(Player* player)
{
    if(IsKeyDown(KEY_LEFT))
    {
        player->turnLeft = true;
    }
    else
    {
         player->turnLeft = false;
    }

    if(IsKeyDown(KEY_RIGHT))
    {
        player->turnRight = true;
    } 
    else
    {
        player->turnRight = false;
    }

    if(IsKeyDown(KEY_UP))
    {
        player->moving = true;
    }
    else
    {
        player->moving = false;
    }
}
void updatePlayer(Player* player,float deltaTime
)
{
    //angular motion
    float rotation = 0.0f;
    if(player->turnRight)
    {
       
        rotation += PLAYER_ANGULAR_SPEED * deltaTime
        ;
    }

    if(player->turnLeft)
    {
        rotation -= PLAYER_ANGULAR_SPEED * deltaTime
        ;
    }

    player->rotation += rotation;

    //player forward speed and displacement
    if(player->moving)
    {
        Vector2 position = player->position;

        position.x += getPlayerDirection(player).x * player->speed * deltaTime
        ;
        position.y += getPlayerDirection(player).y * player->speed * deltaTime
        ;

        if(position.x < 0.0f) position.x = (float)SCREEN_WIDTH - 1.0f;
        else if(position.x > (float)SCREEN_WIDTH) position.x = 1.0f;

        if(position.y < 0.0f) position.y = (float)SCREEN_HEIGHT - 1.0f;
        else if(position.y > (float)SCREEN_HEIGHT) position.y = 1.0f;

        player->position = position;
    }
}
void drawPlayer(Player* player)
{

    //Rectangle rect = {player->texture.width/2.0f,0.0f,player->texture.width/2.0f,
    //player->texture.height/4.0f};

    Rectangle rect = {0,0,128,64};

    Rectangle position = {player->position.x,player->position.y,32,32};


    Vector2 center = {player->texture.width / 2.0f,player->texture.height / 2.0f};
    DrawTexturePro(player->texture,rect,position,center,player->rotation,GREEN);
 
}

Vector2 getPlayerDirection(Player* player)
{
    return (Vector2){cosf(player->rotation*DEG2RAD),sinf(player->rotation*DEG2RAD)};
}

void loadPlayerData(Player* player)
{
    player->texture = LoadTexture("assets/mines.png");
}
void unloadPlayerdata(Player* player)
{
    UnloadTexture(player->texture);
}
