#pragma once
#include <raylib.h>

typedef struct Player
{
    Vector2 position;
    float speed;
    float rotation;

    bool turnRight;
    bool turnLeft;
    bool moving;

    Texture2D *texture;
	Rectangle textureCoord;
} Player;

void initPlayer(Player* player);
void inputPlayer(Player* player);
void updatePlayer(Player* player,float deltatime);
void drawPlayer(Player* player, float scale, Color color);
//void drawPlayer(Player* player, float scale);

Vector2 getPlayerDirection(Player* player);

void loadPlayerData(Player* player);
void unloadPlayerdata(Player* player);

