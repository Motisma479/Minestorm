#include <raylib.h>
#include "Math.h"
#include "collision.h"

#undef main
int main()
{
	InitWindow(3080, 1920,"MINESTORM TEST");
	SetTargetFPS(60);

	Player player = {0};
	player.position = (Vector2d){200, 200};
	player.rotation = 0.0f;

	Circle circle = {{300, 300}, 20};
	Texture2D texture = LoadTexture("./assets/mines.png");
	Rectangle textureCoord = (Rectangle){83, 58, 84, 140};

	//FloatingCollisionBox floating = getFloatingCollisionBox(0, (Vector2d){0, 0}, 1.0f);
	MineLayerCollisionBox mineLayer = getMineLayerCollisionBox(0, (Vector2d){0, 0}, 1.0f);

	//Vector2d center = getCenterConvexPoly(floating.body, sizeof(floating.body) / sizeof(Vector2d));
	Rectangle enemyCoord = (Rectangle){513, 89, 255, 78};

	//Vector2d center = getCenterConvexPoly(mineLayer.poly, sizeof(mineLayer.poly) / sizeof(Vector2d));
	//Vector2d center = (Vector2d){640, 384};
	//Vector2d center = (Vector2d){640.5, 130};

	Vector2d *a = mineLayer.poly;

	int sizeA = ARRAY_SIZE(mineLayer.poly);

	int i;
#if 0
	printf("\n\n\n.poly = {");

	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");

	a = mineLayer.triangle1;
	sizeA = ARRAY_SIZE(mineLayer.triangle1);

	printf(".triangle1 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
	a = mineLayer.triangle2;
	sizeA = ARRAY_SIZE(mineLayer.triangle2);
	printf(".triangle2 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
	a = mineLayer.triangle3;
	sizeA = ARRAY_SIZE(mineLayer.triangle3);
	printf(".triangle3 = {");
	for (i = 0; i < sizeA;i++)
	{
		a[i].x -= center.x;
		a[i].y -= center.y;
		printf("{(%f * scale) + position.x, (%f * scale) + position.y}, \n", a[i].x, a[i].y);
	}
	printf("}\n");
#endif

	//-
	a = mineLayer.poly;
	sizeA = ARRAY_SIZE(mineLayer.poly);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y+ enemyCoord.height / 2;
	}
	a = mineLayer.triangle1;
	sizeA = ARRAY_SIZE(mineLayer.triangle2);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y+ enemyCoord.height / 2;
	}
	a = mineLayer.triangle2;
	sizeA = ARRAY_SIZE(mineLayer.triangle2);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y+ enemyCoord.height / 2;
	}

	a = mineLayer.triangle3;
	sizeA = ARRAY_SIZE(mineLayer.triangle3);
	for (i = 0; i < sizeA;i++)
	{
		a[i].x += enemyCoord.x + enemyCoord.width / 2;
		a[i].y += enemyCoord.y+ enemyCoord.height / 2;
	}

	a = mineLayer.poly;
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

		PlayerCollisionBox pCol = 
			getPlayerCollisionBox(player.rotation*DEG2RAD, (Vector2d) {player.position.x, player.position.y},
								  0.25f);

		DrawTexturePro(texture, enemyCoord, enemyCoord, (Vector2){0, 0}, 0, RED);
		DrawTexturePro(texture, textureCoord, playerPos, origin, player.rotation + 90.0f, WHITE);
		//checkCollisionPlayerFloat(player, getFloatingCollisionBox(0, (Vector2d){0, 0}, 1.0f), 1);
		//checkCollisionPlayerMagnetic(player,  getMagneticCollisionBox(0, (Vector2d){0, 0}, 1.0f), 1);
		//checkCollisionPlayerMagneticFire(player,  fireball, 1);
#if 0
		drawShape(fireball.poly, ARRAY_SIZE(fireball.poly), WHITE);
		drawShape(fireball.triangle1, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle2, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle3, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
		drawShape(fireball.triangle4, sizeof(fireball.triangle1) / sizeof(Vector2d), WHITE);
#endif
		//checkCollisionPlayerMineLayer(player, mineLayer, 1);
#if 0
		drawShape(mineLayer.poly, 4, WHITE);
		drawShape(mineLayer.triangle1, 3, WHITE);
		drawShape(mineLayer.triangle2, 3, WHITE);
		drawShape(mineLayer.triangle3, 3, WHITE);
#endif
		//drawShape(getMineLayerCollisionBox(0, (Vector2d){0, 0}, 1.0f).triangle1, 3, WHITE);
		//drawShape(getMineLayerCollisionBox(0, (Vector2d){0, 0}, 1.0f).triangle2, 3, WHITE);
		//drawShape(getMineLayerCollisionBox(0, (Vector2d){0, 0}, 1.0f).triangle3, 3, WHITE);
		Vector2d *head = pCol.head;
		Vector2d *tail = pCol.tail;

		int sizeHead = sizeof(pCol.head) / sizeof(Vector2d);
		int sizeTail = sizeof(pCol.tail) / sizeof(Vector2d);
		DrawFPS(400, 100);

		Color inter1 = GREEN;

		int intersection1 = satAlgorithmPolygonCircle(head, sizeHead, &circle) || 
			satAlgorithmPolygonCircle(tail, sizeTail, &circle);
		if (intersection1)
			inter1 = RED;
		DrawCircle(circle.center.x, circle.center.y, circle.radius, inter1);

		EndDrawing();
	}

}