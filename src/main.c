#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
//#include "game.h"
#include "Math.h"



int main()
{
	printf("MINE_STORM GAME\n");

	/*Game game;
	bool success = initGame(&game);
	if (success)
	{
		runGameLoop(&game);
	}
	shutdown(&game);
	*/

	//test shape 1
	ConvexPolygon poly;
	poly.nbPoints = GetRandomValue(10,20);
	printf("poly.nbPoints = %d\n",poly.nbPoints);
	poly.points = calloc(0,poly.nbPoints * sizeof(Vector2));

	for(int i = 0; i < poly.nbPoints; i++)
	{
		poly.points[i] = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	}

	int countPoint = 0;
	PolygonShape shape;
	shape.shapes.convexPoly = poly;
	//shape.type = CONVEX_SHAPE;

	getNumberOfVertices(shape,CONVEX_SHAPE,&countPoint);

	printf("The polygon has: %d vertices\n",countPoint);

	//test shape 2
	int countPoint2 = 0;
	Triangle triangle;
	triangle.v1 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	triangle.v2 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	triangle.v3 = (Vector2d){GetRandomValue(-1000,1000) / 10.0f,GetRandomValue(-1000,1000) / 10.0f};
	PolygonShape shape2;
	shape2.shapes.triangle = triangle;

	getNumberOfVertices(shape2,TRIANGLE_SHAPE,&countPoint2);

	printf("The triangle has: %d vertices\n",countPoint2);

	free(poly.points);


	return 0;
}