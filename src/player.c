#include "player.h"
#include "common.h"
#include <math.h>

void initPlayer(Player* player)
{
    player->position.x = SCREEN_WIDTH / 2.0f;
    player->position.y = SCREEN_HEIGHT / 2.0f;
	player->lives = 3;
    player->speed = 10.0f;
    player->rotation = -90.0f;
    player->textureCoord = (Rectangle){83, 58, 84, 140};
}

Vector2 getPlayerDirection(Player* player)
{
    return (Vector2){cosf(player->rotation*DEG2RAD),sinf(player->rotation*DEG2RAD)};
}

void updatePlayer(Player* player, float deltaTime)
{
	static Vector2 acceleration; // We can put this inside player
	Vector2 *position = &player->position;

	//Rotation
	if (player->action & PA_TURN_LEFT)
	{
		player->rotation -= PLAYER_ANGULAR_SPEED * deltaTime;
		player->rotation += (float)ANGULAR_FRICTION * deltaTime;
	}

	if (player->action & PA_TURN_RIGHT)
	{
		player->rotation += PLAYER_ANGULAR_SPEED * deltaTime;
		player->rotation -= (float)ANGULAR_FRICTION * deltaTime;
	}

	if (player->action & PA_TELEPORT)
	{
		teleportingPlayer(player);
	}

	//Movement
    if(player->action & PA_ACCELERATION)
    {
		Vector2 direction = getPlayerDirection(player);

		acceleration.x += direction.x * player->speed;
		acceleration.y += direction.y * player->speed;
	}
	position->x += acceleration.x * deltaTime;
	position->y += acceleration.y * deltaTime;

	// Wraparound
	if (position->x < 64.0f) { position->x = (float)SCREEN_WIDTH - 64.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 64.0f) { position->x = 64.0f; }

	if (position->y < 80.0f) { position->y = (float)SCREEN_HEIGHT - 80.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 80.0f) { position->y = 80.0f; }

	//deacceleration
	acceleration.x -= acceleration.x / 100.0f;
	acceleration.y -= acceleration.y / 100.0f;

	player->action &= ~PA_SHOOT;
}

void drawPlayer(Player* player, float scale, Color color, const Texture2D texture)
{
	Rectangle playerPos =
	{
		player->position.x,
		player->position.y,
		player->textureCoord.width * scale,
		player->textureCoord.height * scale
	};
	//playerPos.x += playerPos.width / 2;
	//playerPos.y += playerPos.height / 2;
	Vector2 origin = {playerPos.width / 2, playerPos.width / 2};

	DrawRectanglePro(playerPos, origin, player->rotation + 90.0f, BLACK);

	DrawTexturePro(texture, player->textureCoord,
				   playerPos, origin, player->rotation + 90.0f, color);
	//DrawCircle();
}

void teleportingPlayer(Player* player)
{
	player->position = (Vector2) {(float)GetRandomValue(64,SCREEN_WIDTH - 64),
		(float)GetRandomValue(80,SCREEN_HEIGHT - 80)};
}
