#pragma once
#include <raylib.h>
#include <stdbool.h>


typedef struct Player
{
	Vector2 position;
	float speed;
	float rotation;
	bool active;
	bool moving;
	bool turnLeft;
	bool turnRight;
	bool teleportation;

	

} Player;


void initPlayer(Player* player);
void inputsPlayer(Player* player);
void updatePlayer(Player* player,float deltaTime);
void drawPlayer(Player* player,const Texture2D* texture);

void teleportingPlayer(Player* player);
Vector2 getPlayerDirection(Player* player);


