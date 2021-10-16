#include "player.h"
#include "commom.h"
#include <math.h>

void initPlayer(Player* player)
{
    player->position.x = SCREEN_WIDTH / 2.0f;
    player->position.y = SCREEN_HEIGHT / 2.0f;
    player->speed = 200.0f;
    player->rotation = 0.0f;
    player->moving = false;
    player->turnRight = false;
    player->turnLeft = false;
	player->textureCoord = (Rectangle){83, 58, 84, 140};
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

void updatePlayer(Player* player, float deltaTime)
{
    //angular motion
    float rotation = 0.0f;
    if(player->turnRight)
		rotation += PLAYER_ANGULAR_SPEED * deltaTime;

    if(player->turnLeft)
		rotation -= PLAYER_ANGULAR_SPEED * deltaTime;

    player->rotation += rotation;

    //player forward speed and displacement
    if(player->moving)
    {
        Vector2 position = player->position;

        position.x += getPlayerDirection(player).x * player->speed * deltaTime;
        position.y += getPlayerDirection(player).y * player->speed * deltaTime;

        if(position.x < 0.0f) position.x = (float)SCREEN_WIDTH - 1.0f;
        else if(position.x > (float)SCREEN_WIDTH) position.x = 1.0f;

        if(position.y < 0.0f) position.y = (float)SCREEN_HEIGHT - 1.0f;
        else if(position.y > (float)SCREEN_HEIGHT) position.y = 1.0f;

        player->position = position;
    }
}

void drawPlayer(Player* player, float scale, Color color)
{
	Rectangle playerPos =
	{
		player->position.x,
		player->position.y,
		player->textureCoord.width * scale,
		player->textureCoord.height * scale
	};
	Vector2 origin = {playerPos.width / 2, playerPos.width / 2};

	//Position.x += game->playArea.x;
	//Position.y += game->playArea.y;

	// Uncomment this to see potential collision wih one single rectangle
	//DrawRectanglePro(playerPos, origin, player->rotation + 90.0f, BLACK);

	DrawTexturePro(*player->texture, player->textureCoord,
				   playerPos, origin, player->rotation + 90.0f, color);
}

Vector2 getPlayerDirection(Player* player)
{
    return (Vector2){cosf(player->rotation*DEG2RAD),sinf(player->rotation*DEG2RAD)};
}
