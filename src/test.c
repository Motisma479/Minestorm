#include <raylib.h>
#include "Math.h"

#include <stdio.h>
int main()
{
	InitWindow(640, 480,"MINESTORM TEST");
	SetTargetFPS(60);

	//PolygonShape poly;

	//poly.type = CONVEX_SHAPE;
	Vector2d a[4];

	a[0] = (Vector2d){20 * 10, 25 * 10};
	a[1] = (Vector2d){40 * 10, 20 * 10};
	a[2] = (Vector2d){40 * 10, 40 * 10};
	a[3] = (Vector2d){20 * 10, 43 * 10};

	Vector2d b[4];

	b[0] = (Vector2d){50 * 4, 55 * 4};
	b[1] = (Vector2d){80 * 4, 50 * 4};
	b[2] = (Vector2d){80 * 4, 80 * 4};
	b[3] = (Vector2d){50 * 4, 83 * 4};

	//poly.shapes.convexPoly.nbPoints = 4;
	//poly.shapes.convexPoly.points = (Vector2d *)&a[0];

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawLine(a->x, a->y, a[1].x, a[1].y, WHITE);
		DrawLine(a[1].x, a[1].y, a[2].x, a[2].y, WHITE);
		DrawLine(a[2].x, a[2].y, a[3].x, a[3].y, WHITE);
		DrawLine(a[3].x, a[3].y, a[0].x, a[0].y, WHITE);

		if (IsKeyDown(KEY_A))
		{
			a[0].x -= 1;
			a[1].x -= 1;
			a[2].x -= 1;
			a[3].x -= 1;
		}
		if (IsKeyDown(KEY_D))
		{
			a[0].x += 1;
			a[1].x += 1;
			a[2].x += 1;
			a[3].x += 1;
		}
		if (IsKeyDown(KEY_S))
		{
			a[0].y += 1;
			a[1].y += 1;
			a[2].y += 1;
			a[3].y += 1;
		}
		if (IsKeyDown(KEY_W))
		{
			a[0].y -= 1;
			a[1].y -= 1;
			a[2].y -= 1;
			a[3].y -= 1;
		}
		int intersecting = 0;
		printf("They are intersecting %d\n", intersecting = satAlgorithm(a, b, 4, 4));
		Color color = WHITE;
		if (intersecting)
			color = RED;
		DrawLine(b->x, b->y, b[1].x, b[1].y, color);
		DrawLine(b[1].x, b[1].y, b[2].x, b[2].y, color);
		DrawLine(b[2].x, b[2].y, b[3].x, b[3].y, color);
		DrawLine(b[3].x, b[3].y, b[0].x, b[0].y, color);

		printf("\e[1;1H\e[2J");
		EndDrawing();
	}

}