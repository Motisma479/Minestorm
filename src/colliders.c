#include "colliders.h"

#include <stdio.h>
#include <raylib.h>
#include <math.h>

//STARTING CREATE PLAYER COLLIDER
typedef struct Particle
{
	Vector2 position;
	Vector2 speed;
	int radius;
} Particle;

static const int screenWidth = 1200;
static const int screenHeight = 900;

bool drawCollider = false;



int main(int argc, char** argv)
{
	printf("COLLIDER...\n");

	InitWindow(screenWidth, screenHeight, "################");
	SetTargetFPS(60);

	Texture2D playerTexture = LoadTexture("assets/mines.png");

	Rectangle textureCoord = (Rectangle){ 83, 58, 84, 140 };
	Rectangle position = { 600,450,64,64 };
	Vector2 origin = { 32.0f,32.0f };
	float rotation = 0.0f;

	Vector2 v1 = (Vector2){ 600, 450 - 34 };
	Vector2 v2 = (Vector2){ 600 - 34, 450 + 34 };
	Vector2 v3 = (Vector2){ 600 + 34, 450 + 34 };

	//barycentric coordinate
	float lambda1 = ((v2.y - v3.y) * (16 - v3.x) + (v3.x - v2.x) * (16 - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
	float lambda2 = ((v3.y - v1.y) * (16 - v3.x) + (v1.x - v3.x) * (16 - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
	float lambda3 = 1 - lambda1 - lambda2;

	//Cartesian coordinates
	float x = lambda1 * v1.x + lambda2 * v2.x + lambda3 * v3.x;
	float y = lambda1 * v1.y + lambda2 * v2.y + lambda3 * v3.y;

	while (!WindowShouldClose())
	{

		if (IsKeyDown(KEY_LEFT))
		{
			rotation -= 5.0f;
		}

		if (IsKeyDown(KEY_RIGHT))
		{
			rotation += 5.0f;
		}

		if (IsKeyPressed(KEY_C))
		{
			drawCollider = !drawCollider;
		}

		

		BeginDrawing();

		ClearBackground(BLACK);

		if(drawCollider)DrawTriangleLines(v1, v2, v3, GREEN);
		DrawTexturePro(playerTexture, textureCoord, position, origin, rotation, SKYBLUE);
		
		


		EndDrawing();
	}

	UnloadTexture(playerTexture);
	CloseWindow();

	return 0;
}
