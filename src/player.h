#pragma once
#include "game.h"
#include "bullet.h"

void    initPlayer(Player* player, Vector2 position);
void    updatePlayer(Player* player, float deltaTime);
void    drawPlayer(Player* player, float scale, Color color,
				   const Texture2D texture);
Vector2 getPlayerDirection(Player* player);
void    loadPlayerData(Player* player);
void    unloadPlayerdata(Player* player);
void    inputsPlayer(Player* player);
void    teleportingPlayer(Player* player);
Vector2 getPlayerDirection(Player* player);
