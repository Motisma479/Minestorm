#include <raylib.h>
#include "Math.h"
#include "collision.h"

#include <stdio.h>

int main()
{
	InitWindow(3080, 1920,"MINESTORM TEST");
	SetTargetFPS(60);

	Player player = {0};
	player.position = (Vector2){200, 200};
	player.rotation = 0.0f;

	//Circle circle = {{300, 300}, 20};
	Texture2D texture = LoadTexture("./assets/mines.png");
	Rectangle textureCoord = (Rectangle){83, 58, 84, 140};

	//FloatingCollisionBox floating = getFloatingCollisionBox(0, (Vector2d){0, 0}, 1.0f);
	MagneticFireBallCollisionBox fireball = getMagneticFireballCollisionBox(0, (Vector2d){0, 0}, 1.0f);

	//Vector2d center = getCenterConvexPoly(floating.body, sizeof(floating.body) / sizeof(Vector2d));
	Rectangle enemyCoord = (Rectangle){567, 308, 149, 153};

	//Vector2d center = getCenterConvexPoly(fireball.poly, sizeof(fireball.poly) / sizeof(Vector2d));
	//Vector2d center = (Vector2d){640, 384};

	Vector2d *a = fireball.poly;

	int sizeA = sizeof(fireball.poly) / sizeof(Vector2d);

#if 0
	int i;
	printf("\n\n\n.poly = {");

	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");

	a = fireball.triangle1;
	sizeA = sizeof(fireball.triangle1) / sizeof(Vector2d);

	printf(".triangle1 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
	a = fireball.triangle2;
	sizeA = sizeof(fireball.triangle2) / sizeof(Vector2d);
	printf(".triangle2 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
	a = fireball.triangle3;
	sizeA = sizeof(fireball.triangle2) / sizeof(Vector2d);
	printf(".triangle3 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
	printf(".triangle4 = {");
	a = fireball.triangle4;
	sizeA = sizeof(fireball.triangle2) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
#endif

	//-
	int i;
	a = fireball.poly;
	sizeA = sizeof(fireball.poly) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y + enemyCoord.height / 2;
	}
	a = fireball.triangle1;
	sizeA = sizeof(fireball.triangle2) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y + enemyCoord.height / 2;
	}
	a = fireball.triangle2;
	sizeA = sizeof(fireball.triangle2) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y + enemyCoord.height / 2;
	}

	a = fireball.triangle3;
	sizeA = sizeof(fireball.triangle3) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y + enemyCoord.height / 2;
	}

	a = fireball.triangle4;
	sizeA = sizeof(fireball.triangle4) / sizeof(Vector2d);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y + enemyCoord.height / 2;
	}
	a = fireball.poly;

	//printf("};\n");

	while (!WindowShouldClose())
	{

		Rectangle playerPos =
		{
			player.position.x,
			player.position.y,
			textureCoord.width * 0.25,
			textureCoord.height * 0.25
		};

		Vector2 origin = {playerPos.width / 2, playerPos.height / 2 + (18 * 0.25f)};

		BeginDrawing();
		ClearBackground(BLACK);

		//FloatingCollisionBox enemyColBox = getFloatingCollisionBox(0, (Vector2d){0, 0});
		//MagneticCollisionBox fireColBox =  getEnemyCollisionBox2(0, (Vector2d){0, 0});

		if (IsKeyDown(KEY_A))
			player.position.x -= 1;
		if (IsKeyDown(KEY_D))
			player.position.x += 1;
		if (IsKeyDown(KEY_S))
			player.position.y += 1;
		if (IsKeyDown(KEY_W))
			player.position.y -= 1;
		if (IsKeyDown(KEY_E))
			player.rotation += 0.1f;
		if (IsKeyDown(KEY_Q))
			player.rotation -= 0.1f;


		DrawTexturePro(texture, enemyCoord, enemyCoord, (Vector2){0, 0}, 0, RED);
		DrawTexturePro(texture, textureCoord, playerPos, origin, player.rotation*RAD2DEG, WHITE);
		checkCollisionPlayerFloat(player, getFloatingCollisionBox(0, (Vector2d){0, 0}, 1.0f), 1);
		checkCollisionPlayerMagnetic(player,  getMagneticCollisionBox(0, (Vector2d){0, 0}, 1.0f), 1);
		//checkCollisionPlayerFireBall(player, fireball, 1);
		checkCollisionPlayerMagneticFireBall(player,  fireball, 1);
		//sizeof(fireball.poly) / sizeof(Vector2d)
#if 0
		drawShape(fireball.poly, sizeof(fireball.poly) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle1, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle2, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle3, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle4, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
#endif

		//drawShape(fireball.triangle1, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		//drawShape(fireball.triangle2, sizeof(fireball.triangle2) / sizeof(Vector2d), WHITE);

		DrawFPS(400, 100);
#if 0
		if (intersection1)
			inter1 = RED;
		DrawCircle(circle.center.x, circle.center.y, circle.radius, inter1);
#endif
		EndDrawing();
	}

}