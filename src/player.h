


/*typedef struct Player
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
*/

#pragma once
#include "game.h"
#include "bullet.h"

void    initPlayer(Player* player, Vector2d position);
void    updatePlayer(Player* player, float deltaTime);
void    drawPlayer(Player* player, float scale, Color color,
				   const Texture2D* texture);

void    loadPlayerData(Player* player);
void    unloadPlayerdata(Player* player);
void    inputsPlayer(Player* player);
void    teleportingPlayer(Player* player);

