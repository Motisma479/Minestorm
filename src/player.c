#include "player.h"
#include "commom.h"
#include <math.h>

void initPlayer(Player* player)
{
	player->position = (Vector2){SCREEN_WIDTH /2.0f,SCREEN_HEIGHT /2.0f};
	player->rotation = 0.0f;
	player->speed = 200.0f;
	player->active = false;
	player->moving = false;
	player->turnLeft = false;
	player->turnRight = false;
}

void inputsPlayer(Player* player)
{
	//turn left
	if (IsKeyDown(KEY_D))
	{
		player->turnLeft = true;
	}
	else
	{
		player->turnLeft = false;
	}

	//turn right
	if (IsKeyDown(KEY_G))
	{
		player->turnRight = true;
	}
	else
	{
		player->turnRight = false;
	}

	//moving
	if (IsKeyDown(KEY_R))
	{
		player->moving = true;
	}
	else
	{
		player->moving = false;
	}

	//shoot
	if (IsKeyDown(KEY_F))
	{

	}

	//Teleport
	if (IsKeyDown(KEY_T))
	{
		player->teleportation = true;
	}
	else
	{
		player->teleportation = false;
	}
}
void updatePlayer(Player* player,float deltaTime)
{
	float rotation = 0.0f;
	if (player->turnLeft)
	{
		rotation -= PLAYER_ANGULAR_SPEED * deltaTime;
		rotation += (float)ANGULAR_FRICTION * deltaTime;
	}

	if (player->turnRight)
	{
		rotation += PLAYER_ANGULAR_SPEED * deltaTime;
		rotation -= (float)ANGULAR_FRICTION * deltaTime;
	}

	player->rotation += rotation;
	

	if (player->teleportation)
	{
		teleportingPlayer(player);
	}

	if (player->moving)
	{
		Vector2 position = player->position;

		position.x += getPlayerDirection(player).x * player->speed * deltaTime;
		position.y += getPlayerDirection(player).y * player->speed * deltaTime;

		if (position.x < 64.0f) { position.x = (float)SCREEN_WIDTH - 64.0f; }
		else if (position.x > (float)SCREEN_WIDTH - 64.0f) { position.x = 64.0f; }

		if (position.y < 80.0f) { position.y = (float)SCREEN_HEIGHT - 80.0f; }
		else if (position.y > (float)SCREEN_HEIGHT - 80.0f) { position.y = 80.0f; }

		player->position = position;
	}
}
void drawPlayer(Player* player, const Texture2D* texture)
{
	Rectangle rect = { 0.0f,0.0f,texture->width / 4.0f,texture->height / 2.0f };
	Rectangle position = { player->position.x,player->position.y,64.0f,64.0f };
	Vector2 center = { 32.0f,32.0f };
	//if (!player->teleportation && player->active)
	//{
		//DrawTexturePro(texture, rect, position, center, player->rotation, SKYBLUE);
	//}
	//Vector2 points = {100.0f,100.0f};
	//Vector2 textCoords = {player->position.x,player->position.y};
	if (player->active)
	{
		if (!player->teleportation)
		{
			DrawTexturePro(*texture, rect, position, center, player->rotation, SKYBLUE);
			//DrawTexturePoly(texture,center,&points,&textCoords,100,GREEN);
		}
	}

}
void teleportingPlayer(Player* player)
{
	Vector2 position = { (float)GetRandomValue(64,SCREEN_WIDTH - 64),
		(float)GetRandomValue(80,SCREEN_HEIGHT - 80) };

	player->position = position;
}
Vector2 getPlayerDirection(Player* player)
{
	return (Vector2){cosf(player->rotation*DEG2RAD - PI / 2.0f),sinf(player->rotation * DEG2RAD - PI / 2.0f)};
}
