#include <raylib.h>
#include "Math.h"

#include <stdio.h>


typedef struct Player
{
	int          bulletCount;
    Vector2      position;
	Vector2      acceleration;
    float        rotation;
	Rectangle    textureCoord;
} Player;

int main()
{
	InitWindow(640, 480,"MINESTORM TEST");
	SetTargetFPS(120);

	float    rotation = 0.0f;
	Vector2d a[] = {{123, 58}, {106, 99}, {110, 130}, {139, 130}, {143, 99},
		{126, 58}};

	Vector2d b[] = {{110, 130}, {94, 130}, {83, 178}, {93, 197}, {156, 197},
		{166, 178}, {150, 130}, {139, 130}};

	Vector2d a2[] = {{123, 58}, {106, 99}, {110, 130}, {139, 130}, {143, 99},
		{126, 58}};

	Vector2d b2[] = {{110, 130}, {94, 130}, {83, 178}, {93, 197}, {156, 197},
		{166, 178}, {150, 130}, {139, 130}};


	//Vector2d c[] = {a[0], a[1], a[2], b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], a[4], a[5]};
	Vector2d c[] = {a[0], a[1], a[2], b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], a[4], a[5]};

	Vector2d a1[6];
	Vector2d b1[8];

	int sizeA = sizeof(a) / sizeof(Vector2d);
	int sizeB = sizeof(b) / sizeof(Vector2d);
	int sizeC = sizeof(c) / sizeof(Vector2d);

	Vector2d center = getCenterConvexPoly(c, sizeC);
	Vector2d position = {200, 200};

	int i;
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
	}
	for (i = 0; i < sizeB;i++)
	{
		b[i].x -= center.x;
		b[i].y -= center.y;
	}

	Circle circle = {{300, 300}, 20};
	Texture2D texture = LoadTexture("./assets/mines.png");
	Rectangle textureCoord = (Rectangle){83, 58, 84, 140};
	//Color colors[] = {WHITE, RED, GREEN, BLUE, LIME, SKYBLUE, YELLOW, PINK};

	while (!WindowShouldClose())
	{
		Rectangle playerPos =
		{
			position.x,
			position.y,
			textureCoord.width,
			textureCoord.height
		};

		Vector2 origin = {playerPos.width / 2, playerPos.height / 2 + 20};

		BeginDrawing();
		ClearBackground(BLACK);

		if (IsKeyDown(KEY_A))
			position.x -= 1;
		if (IsKeyDown(KEY_D))
			position.x += 1;
		if (IsKeyDown(KEY_S))
			position.y += 1;
		if (IsKeyDown(KEY_W))
			position.y -= 1;
		if (IsKeyDown(KEY_E))
		{
			rotation += 0.1f;
		}
		if (IsKeyDown(KEY_Q))
		{
			rotation -= 0.1f;
		}

		for (i = 0; i < sizeA;i++)
		{
			a1[i].x = (a[i].x * cosf(rotation) - a[i].y*sinf(rotation)) + position.x;
			a1[i].y = (a[i].x * sinf(rotation) + a[i].y*cosf(rotation)) + position.y;
		}
		for (i = 0; i < sizeB;i++)
		{
			b1[i].x = (b[i].x * cosf(rotation) - b[i].y*sinf(rotation)) + position.x;
			b1[i].y = (b[i].x * sinf(rotation) + b[i].y*cosf(rotation)) + position.y;
		}
		int intersection = satAlgorithm(a2, a1, sizeA, sizeA) || satAlgorithm(a2, b1, sizeA, sizeB) ||
			satAlgorithm(b2, a1, sizeB, sizeA) || satAlgorithm(b2, b1, sizeB, sizeB);

		int intersection1 = satAlgorithmPolygonCircle(a1, sizeA, &circle) || satAlgorithmPolygonCircle(b1, sizeB, &circle);

		Color inter = GREEN;
		Color inter1 = GREEN;
		if (intersection)
			inter = RED;
		for (i = 0; i < sizeA - 1;i++)
			DrawLine(a1[i].x, a1[i].y, a1[i+1].x, a1[i+1].y, WHITE);
		DrawLine(a1[i].x, a1[i].y, a1[0].x, a1[0].y, WHITE);
		for (i = 0; i < sizeB - 1;i++)
			DrawLine(b1[i].x, b1[i].y, b1[i+1].x, b1[i+1].y, WHITE);
		DrawLine(b1[i].x, b1[i].y, b1[0].x, b1[0].y, WHITE);

		for (i = 0; i < sizeA - 1;i++)
			DrawLine(a2[i].x, a2[i].y, a2[i+1].x, a2[i+1].y, inter);
		DrawLine(a2[i].x, a2[i].y, a2[0].x, a2[0].y, inter);
		for (i = 0; i < sizeB - 1;i++)
			DrawLine(b2[i].x, b2[i].y, b2[i+1].x, b2[i+1].y, inter);
		DrawLine(b2[i].x, b2[i].y, b2[0].x, b2[0].y, inter);

#if 0
		for (i = 0; i < sizeC - 1;i++)
			DrawLine(c[i].x, c[i].y, c[i + 1].x, c[i + 1].y, inter);
		DrawLine(c[i].x, c[i].y, c[0].x, c[0].y, inter);
#endif
		DrawTexturePro(texture, textureCoord, playerPos, origin, rotation*RAD2DEG, WHITE);
		DrawFPS(400, 100);
		if (intersection1)
			inter1 = RED;
		DrawCircle(circle.center.x, circle.center.y, circle.radius, inter1);
		EndDrawing();
	}

}