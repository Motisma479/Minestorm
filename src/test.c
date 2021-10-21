#include <raylib.h>
#include "Math.h"

typedef struct ShipCollisionShape
{
	Vector2d head[8];
	Vector2d tail[6];
} ShipCollisionShape;

#include <stdio.h>

Vector2d getCenter(Vector2d *v, int size)
{
	Vector2d result = {0};
	int i = 0;
	float areaSum = 0.0f;
	float area = 0.0f;
	for (i = 0;i < size - 1;i++){

		area = v[i].x*v[i+1].y - v[i+1].x*v[i].y;
		areaSum += area;
		result.x += (v[i].x + v[i+1].x) * area;
		result.y += (v[i].y + v[i+1].y) * area;
	}
	area = v[i].x*v[0].y - v[i].x*v[0].y;
	areaSum += area;
	areaSum *= 0.5;
	result.x = result.x / (areaSum*6.0f);
	result.y = result.y / (areaSum*6.0f);
	return (result);
}

int main()
{
	InitWindow(640, 480,"MINESTORM TEST");
	SetTargetFPS(60);

	//PolygonShape poly;

	//poly.type = CONVEX_SHAPE;
	int sizeA = 8;
	int sizeB = 6;
	Vector2d a[8];
	float    rotation = 0.01f;

	a[0] = (Vector2d){110, 130};
	a[1] = (Vector2d){94, 130};
	a[2] = (Vector2d){83, 178};
	a[3] = (Vector2d){93, 197};
	a[4] = (Vector2d){156, 197};
	a[5] = (Vector2d){166, 178};
	a[6] = (Vector2d){150, 130};
	a[7] = (Vector2d){110, 130};

	Vector2d b[6];

	b[0] = (Vector2d){123, 58};
	b[1] = (Vector2d){106, 99};
	b[2] = (Vector2d){110, 130};
	b[3] = (Vector2d){139, 130};
	b[4] = (Vector2d){143, 99};
	b[5] = (Vector2d){126, 58};

	//poly.shapes.convexPoly.nbPoints = 4;
	//poly.shapes.convexPoly.points = (Vector2d *)&a[0];
	while (!WindowShouldClose())
	{
		Vector2d center = getCenter(a, 8);
		Vector2d center2 = getCenter(b, 6);
		printf("%f, %f\n", center.x, center.y);
		BeginDrawing();
		ClearBackground(BLACK);
		int i;

		for (i = 0; i < sizeA - 1;i++){
			DrawLine(a[i].x, a[i].y, a[i + 1].x, a[i + 1].y, WHITE);
		}
		//DrawLine(a[i - 1].x, a[i - 1].y, a[0].x, a[0].y, WHITE);

		if (IsKeyDown(KEY_A))
		{
			for (i = 0; i < sizeA;i++)
				a[i].x -= 1;
			for (i = 0; i < sizeB;i++)
				b[i].x -= 1;

		}
		if (IsKeyDown(KEY_D))
		{
			for (i = 0; i < sizeA;i++)
				a[i].x += 1;
			for (i = 0; i < sizeB;i++)
				b[i].x += 1;
		}
		if (IsKeyDown(KEY_S))
		{
			for (i = 0; i < sizeA;i++)
				a[i].y += 1;
			for (i = 0; i < sizeB;i++)
				b[i].y += 1;
		}
		if (IsKeyDown(KEY_W))
		{
			for (i = 0; i < sizeA;i++)
				a[i].y -= 1;
			for (i = 0; i < sizeB;i++)
				b[i].y -= 1;
		}
		if (IsKeyDown(KEY_E))
		{
			for (i = 0; i < sizeA;i++)
			{
				// = center;
				a[i].x -= center.x;
				a[i].y -= center.y;
				a[i].x = a[i].x * cosf(rotation) - a[i].y*sinf(rotation);
				a[i].y = a[i].x * sinf(rotation) + a[i].y*cosf(rotation);
				a[i].x += center.x;
				a[i].y += center.y;
			}
			for (i = 0; i < sizeB;i++)
			{
				// = center;
				b[i].x -= center2.x;
				b[i].y -= center2.y;
				b[i].x = b[i].x * cosf(rotation) - b[i].y*sinf(rotation);
				b[i].y = b[i].x * sinf(rotation) + b[i].y*cosf(rotation);
				b[i].x += center2.x;
				b[i].y += center2.y;
			}
		}

		if (IsKeyDown(KEY_Q))
		{
			for (i = 0; i < sizeA;i++)
			{
				// = center;
				a[i].x -= center.x;
				a[i].y -= center.y;
				a[i].x = a[i].x * cosf(-rotation) - a[i].y*sinf(-rotation);
				a[i].y = a[i].x * sinf(-rotation) + a[i].y*cosf(-rotation);
				a[i].x += center.x;
				a[i].y += center.y;
			}
			for (i = 0; i < sizeB;i++)
			{
				// = center;
				b[i].x -= center2.x;
				b[i].y -= center2.y;
				b[i].x = b[i].x * cosf(-rotation) - b[i].y*sinf(-rotation);
				b[i].y = b[i].x * sinf(-rotation) + b[i].y*cosf(-rotation);
				b[i].x += center2.x;
				b[i].y += center2.y;
			}
		}

		int intersecting = 0;
		printf("They are intersecting %d\n", intersecting = satAlgorithm(a, b, 8, 6));
		Color color = GREEN;
		if (intersecting)
			color = RED;

		for (i = 0; i < 5;i++)
			DrawLine(b[i].x, b[i].y, b[i + 1].x, b[i + 1].y, color);
		DrawLine(b[i].x, b[i].y, b[0].x, b[0].y, color);

		printf("\e[1;1H\e[2J");
		EndDrawing();
	}

}