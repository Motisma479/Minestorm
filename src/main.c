#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
//#include "game.h"
#include "Math.h"



int main(void)
{
	printf("MINE_STORM GAME\n");

	InitWindow(800,600,"[--MATHIEU-VICTOR-OSVALDO--GP1--MINESTORM PROJECT--ISART DIGITAL--]");
	SetTargetFPS(60);

	//for test SAT(triangle - triangle)
	Triangle triangle1;
	triangle1.v1 = (Vector2d){400.0f,50.0f};
	triangle1.v2 = (Vector2d){150.0f,150.0f};
	triangle1.v3 = (Vector2d){650.0f,200.0f};

	Vector2 v11 = {0};
	Vector2 v12 = {0};
	Vector2 v13 = {0};
	v11 = (Vector2){triangle1.v1.x,triangle1.v1.y};
	v12 = (Vector2){triangle1.v2.x,triangle1.v2.y};
	v13 = (Vector2){triangle1.v3.x,triangle1.v3.y};

	Triangle triangle2;
	//triangle2.v1 = (Vector2d){10.0f,10.0f};
	//triangle2.v2 = (Vector2d){10.0f,20.0f};
	//triangle2.v3 = (Vector2d){30.0f,5.0f};
	triangle2.v1 = (Vector2d){10.0f,600.0f};
	triangle2.v2 = (Vector2d){10.0f,700.0f};
	triangle2.v3 = (Vector2d){15.0f,650.0f};

	Vector2 v21 = {0};
	Vector2 v22 = {0};
	Vector2 v23 = {0};
	v21 = (Vector2){triangle2.v1.x,triangle2.v1.y};
	v22 = (Vector2){triangle2.v2.x,triangle2.v2.y};
	v23 = (Vector2){triangle2.v3.x,triangle2.v3.y};

	PolygonShape tr1;
	PolygonShape tr2;
	tr1.type = TRIANGLE_SHAPE;
	tr2.shapes.triangle = triangle1;
	tr2.type = TRIANGLE_SHAPE;
	tr2.shapes.triangle = triangle2;

	Vector2d a[3] = {triangle1.v1,triangle1.v2,triangle1.v3};
	Vector2d b[3] = {triangle2.v1,triangle2.v2,triangle2.v3};
	

	int isColliding = satAlgorithm(a,b,3,3);

	printf("IsCollinding = %d\n",isColliding);


	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);


		DrawTriangleLines(v11,v12,v13,PURPLE);

		DrawTriangleLines(v21,v22,v23,PINK);

		EndDrawing();
	}
	CloseWindow();



	/*Game game;
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);
	*/

	//test shape 1
	/*ConvexPolygon poly;
	poly.nbPoints = GetRandomValue(10,20);
	printf("poly.nbPoints = %d\n",poly.nbPoints);
	poly.points = calloc(0,poly.nbPoints * sizeof(Vector2));

	for(int i = 0; i < poly.nbPoints; i++)
	{
		poly.points[i] = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	}*/

	//int countPoint = 0;
	//PolygonShape shape;
	//shape.shapes.convexPoly = poly;
	//shape.type = CONVEX_SHAPE;

	//getNumberOfVertices(shape,CONVEX_SHAPE,&countPoint);

	//printf("The polygon has: %d vertices\n",countPoint);

	//test shape 2
	/*int countPoint2 = 0;
	Triangle triangle;
	triangle.v1 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	triangle.v2 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	triangle.v3 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	PolygonShape shape2;
	shape2.shapes.triangle = triangle;

	getNumberOfVertices(shape2,TRIANGLE_SHAPE,&countPoint2);

	printf("The triangle has: %d vertices\n",countPoint2);

	free(poly.points);*/


	return 0;
}