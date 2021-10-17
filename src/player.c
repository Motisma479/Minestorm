#include "player.h"
#include "commom.h"
#include <math.h>

void initPlayer(Player* player)
{
    player->position.x = SCREEN_WIDTH / 2.0f;
    player->position.y = SCREEN_HEIGHT / 2.0f;
    player->speed = 10.0f;
    player->rotation = 0.0f;
    player->moving = false;
    player->textureCoord = (Rectangle){83, 58, 84, 140};
}

void updatePlayer(Player* player, float deltaTime)
{
	static Vector2 acceleration; // We can put this inside player
	Vector2 *position = &player->position;

	//Rotation
	if(IsKeyDown(KEY_LEFT))
		player->rotation -= PLAYER_ANGULAR_SPEED * deltaTime;
	if(IsKeyDown(KEY_RIGHT))
		player->rotation += PLAYER_ANGULAR_SPEED * deltaTime;

	//Movement
    if(player->moving)
    {
		Vector2 direction = getPlayerDirection(player);

		acceleration.x += direction.x * player->speed;
		acceleration.y += direction.y * player->speed;
	}
	position->x += acceleration.x * deltaTime;
	position->y += acceleration.y * deltaTime;

	// Wraparound
	if(position->x < 0.0f) position->x = (float)SCREEN_WIDTH - 1.0f;
	else if(position->x > (float)SCREEN_WIDTH) position->x = 1.0f;

	if(position->y < 0.0f) position->y = (float)SCREEN_HEIGHT - 1.0f;
	else if(position->y > (float)SCREEN_HEIGHT) position->y = 1.0f;

	//deacceleration
	acceleration.x -= acceleration.x / 100.0f;
	acceleration.y -= acceleration.y / 100.0f;
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

	// Uncomment this to see the collision box
	//DrawRectanglePro(playerPos, origin, player->rotation + 90.0f, BLACK);

	DrawTexturePro(*player->texture, player->textureCoord,
				   playerPos, origin, player->rotation + 90.0f, color);
}

Vector2 getPlayerDirection(Player* player)
{
    return (Vector2){cosf(player->rotation*DEG2RAD),sinf(player->rotation*DEG2RAD)};
}
