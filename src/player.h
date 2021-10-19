#pragma once
#include <raylib.h>

typedef enum PlayerAction
{
	PA_ACCELERATION = 1UL,
	PA_TURN_LEFT    = 1UL << 1,
	PA_TURN_RIGHT   = 1UL << 2,
	PA_TELEPORT     = 1UL << 3,
	PA_SHOOT        = 1UL << 4,
} PlayerAction;

typedef struct Player
{
    Vector2      position;
	Vector2      acceleration;
    float        rotation;
	int          lives;
	int          score;
	PlayerAction action;
	Rectangle    textureCoord;
} Player;

void    initPlayer(Player* player);
void    updatePlayer(Player* player,float deltatime);
void    drawPlayer(Player* player, float scale, Color color,
				   const Texture2D texture);
Vector2 getPlayerDirection(Player* player);
void    loadPlayerData(Player* player);
void    unloadPlayerdata(Player* player);
void    inputsPlayer(Player* player);
void    teleportingPlayer(Player* player);
Vector2 getPlayerDirection(Player* player);
