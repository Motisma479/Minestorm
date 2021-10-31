#include "player.h"
#include "common.h"
#include <math.h>
#include <raylib.h>

void initPlayer(Player* player, Vector2d position)
{
	player->position = position;
    player->lives = 3;
	player->rotation = -90.0f;
}

void updatePlayer(Player* player, float deltaTime)
{
	if (player->lives > 0)
	{
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
			teleportingPlayer(player);

		//Movement
		if(player->action & PA_ACCELERATION)
		{
			Vector2d direction = getDirection(player->rotation);

			player->acceleration.x += direction.x * PLAYER_SPEED;
			player->acceleration.y += direction.y * PLAYER_SPEED;
		}
		player->position.x += player->acceleration.x * deltaTime;
		player->position.y += player->acceleration.y * deltaTime;

		// Wraparound
		if (player->position.x < 64.0f) { player->position.x = (float)SCREEN_WIDTH - 64.0f; }
		else if (player->position.x > (float)SCREEN_WIDTH - 64.0f) { player->position.x = 64.0f; }

		if (player->position.y < 80.0f) { player->position.y = (float)SCREEN_HEIGHT - 80.0f; }
		else if (player->position.y > (float)SCREEN_HEIGHT - 80.0f) { player->position.y = 80.0f; }

		float friction = 20.0f;

		//deacceleration
		player->acceleration.x -= player->acceleration.x / friction;
		player->acceleration.y -= player->acceleration.y / friction;
	}
}

void drawPlayer(Player* player, float scale, Color color, const Texture2D texture)
{
	if (player->lives > 0)
	{
		Rectangle textureCoord = (Rectangle){83, 58, 84, 140};
		Rectangle playerPos =
		{
			player->position.x,
			player->position.y,
			textureCoord.width * scale,
			textureCoord.height * scale
		};
		Vector2 origin = {playerPos.width / 2, (playerPos.height / 2) + 5};

		DrawTexturePro(texture, textureCoord,
					   playerPos, origin, player->rotation + 90.0f, color);
	}
}

void teleportingPlayer(Player* player)
{
	player->position = (Vector2d) {(float)GetRandomValue(64,SCREEN_WIDTH - 64),
		(float)GetRandomValue(80,SCREEN_HEIGHT - 80)};
}
