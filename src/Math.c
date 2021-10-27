#include "Math.h"
#include <stdio.h>

Vector2 zeroVector2()
{
    return (Vector2){0.0f,0.0f};
}
Vector2 addVector2(Vector2 a,Vector2 b)
{
    return (Vector2){a.x + b.x, a.y + b.y};
}
Vector2 subsVector2(Vector2 a,Vector2 b)
{
    return (Vector2){a.x - b.x, a.y - b.y};
}
bool isEqualToVector2(Vector2 a,Vector2 b)
{
    bool test = (a.x - b.x) >= -EPSILON  && (a.x - b.x) <= EPSILON && 
		(a.y - b.y) >= -EPSILON  && (a.y - b.y) <= EPSILON;

    return test;
}
Vector2 normalizeVector2(Vector2 v)
{
    float length = lengthVector2(v);
    if(length == 0.0f)
        return zeroVector2();

    Vector2 vector;
    vector.x = v.x / length;
    vector.y = v.y / length;

    return vector;
}
Vector2 negateVector2(Vector2 v)
{
    return (Vector2){-v.x,-v.y};
}

float lengthSqVector2(Vector2 v)
{
    return (v.x*v.x + v.y*v.y);
}
float lengthVector2(Vector2 v)
{
    return sqrtf(lengthSqVector2(v));
}

Vector2 scaleVector2(Vector2 v,float scalar)
{
    return (Vector2){v.x * scalar, v.y * scalar};
}
float distVector2(Vector2 a, Vector2 b)
{
    return lengthVector2(subsVector2(a,b));
}

float dotProduct(Vector2 a,Vector2 b)
{
    return (a.x * b.x + a.y * b.y);
}

float lerp(float a,float b,float t)
{
    return (1.0f - t) * a + b * t;
}
float inverseLerp(float a,float b,float value)
{
    return (value - a) / (b - a);
}


Vector2 pointOnLineSegment(LineSegment segment, float t)
{
    Vector2 seg;
    seg.x = segment.start.x + subsVector2(segment.start,segment.end).x * t;
    seg.y = segment.start.y + subsVector2(segment.start,segment.end).y * t;

    return seg;
}
bool testPointCircle(Vector2 point,Circle c)
{
    float distSq =(distVector2(point, c.center));
    distSq *= distSq;


    return distSq <= c.radius * c. radius;
}
bool testPointRect(Vector2 point, AABB rect)
{
    bool outside = point.x < rect.min.x ||
		point.y < rect.min.y ||
		point.x > rect.max.x ||
		point.y > rect.max.y;

    //If none of these are true, they must intersect
    return !outside; 
}
bool testRect(AABB r1,AABB r2)
{
    bool collision = r1.max.x < r2.min.x ||
		r1.max.y < r2.min.y ||
		r2.max.x < r1.min.x ||
		r2.max.y < r1.min.y;

    //If none of these are true, they must intersect
    return !collision;
}

bool testCircle(Circle c1,Circle c2)
{
    float distSq = distVector2(c1.center,c2.center);
    distSq *= distSq;

    float radiSq = c1.radius + c2.radius;
    radiSq *= radiSq;

    return distSq <= radiSq;
}

bool testCircleRect(Circle c, AABB rect)
{
    float distX;
    float distY;

    if(c.center.x < rect.min.x) distX = rect.min.x;
    else distX = rect.max.x;

    if(c.center.y < rect.min.y) distY = rect.min.y;
    else distY = rect.max.y;

    float distSq = lengthSqVector2((Vector2){distX,distY});

    return distSq <= c.radius * c.radius;

}

/*int countVertices(PolygonShape)
{

}
*/

/*void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices)
{
	//int count;
	shape.type = type;

    switch (shape.type)
    {
        case POINT_SHAPE:
		*nbVertices = 1;
		break;
        case SEGMENT_SHAPE:
		*nbVertices = 2;
		break;
        case TRIANGLE_SHAPE:
		*nbVertices = 3;
		break;
        case AABB_SHAPE:
		*nbVertices = 4;
		break;
        case OBB_SHAPE:
		*nbVertices = 4;
		break;
        case CONVEX_SHAPE:
		for(int i = 0; i < shape.shapes.convexPoly.nbPoints; i++)
		{
			Vector2* p1 = &shape.shapes.convexPoly.points[i];
			//Next vertex;
			Vector2* p2 = &shape.shapes.convexPoly.points[ i + 1 == shape.shapes.convexPoly.nbPoints ? 0 : i+1 ];

			if(!isEqualToVector2(*p1,*p2))
			{
				*nbVertices += 1;
			}
		}
		break;
        default:
		break;
    }
}
*/

Range getMinRange(Range r1, Range r2)
{
	Range r = {0};
	r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r2 : r1;
	return r;
}
Range getMaxRange(Range r1, Range r2)
{
	Range r = {0};
	r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r1 : r2;
	return r;
}
bool rangeOverlapRange(Range r1, Range r2)
{
	return (r1.min <= r2.max) && (r2.min <= r1.max);
}
Vector2 getNormal(Vector2 a, Vector2 b)
{
	Vector2 result;

	result.x = -(b.y - a.y);
	result.y = (b.x - a.x);
	//result = normalizeVector2(result);
	return (result);
}

Vector2 getLocalVector2(Vector2 a, Vector2 b)
{
	Vector2 result = {b.x - a.x, b.y - a.y};

	return (result);
}

Vector2 rotateAndTranslate(Vector2 vector, float rotation, Vector2 position)
{
	Vector2 result = {
		.x = (vector.x * cosf(rotation) - vector.y*sinf(rotation)) + position.x,
		.y = (vector.x * sinf(rotation) + vector.y*cosf(rotation)) + position.y};
	return (result);
}

Vector2 getCenterConvexPoly(Vector2 *v, int size)
{
	Vector2 result = {0};
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

int satAlgorithm(Vector2 *a, Vector2 *b, int sizeA, int sizeB)
{
	float infinity = 1.0f / 0.0f;
	float minusInfinity = log(0);

	for (int i = 0; i < sizeA - 1;i++)
	{
		Range range1 = {infinity, minusInfinity};
		Range range2 = range1;

		Vector2 normal = getNormal(a[i], a[i + 1]);
		for (int j = 0; j < sizeA;j++)
		{
			float projection = dotProduct(a[j], normal);
			if (projection < range1.min)
				range1.min = projection;
			if (projection > range1.max)
				range1.max = projection;
		}

		for (int j = 0;j < sizeB;j++)
		{
			float projection = dotProduct(b[j], normal);

			if (projection < range2.min)
				range2.min = projection;
			if (projection > range2.max)
				range2.max = projection;
		}
		if(!rangeOverlapRange(range1,range2))
			return 0;
	}
	return 1;
}

int satAlgorithmPolygonCircle(Vector2* v,int vSize,Circle *circle)
{
	float infinity = 1.0f / 0.0f;
	float minusInfinity = log(0);

	for (int i = 0; i < vSize - 1;i++)
	{
		Range range1 = {infinity, minusInfinity};
		Range range2 = range1;

		Vector2 normal = getNormal(v[i], v[i + 1]);
		for (int j = 0; j < vSize;j++)
		{
			float projection = dotProduct(v[j], normal);
			if (projection < range1.min)
				range1.min = projection;
			if (projection > range1.max)
				range1.max = projection;
		}

		for (int j = 0;j < vSize;j++)
		{
			Vector2 normalized = normalizeVector2(normal);


			float projection1 = dotProduct((Vector2){circle->center.x + (normalized.x * circle->radius), circle->center.y + (normalized.y * circle->radius)}, normal);
			float projection2 = dotProduct((Vector2){circle->center.x - (normalized.x * circle->radius), circle->center.y - (normalized.y * circle->radius)}, normal);

			if (projection1 < range2.min)
				range2.min = projection1;
			if (projection1 > range2.max)
				range2.max = projection1;
			if (projection2 < range2.min)
				range2.min = projection2;
			if (projection2 > range2.max)
				range2.max = projection2;
		}
		if(!rangeOverlapRange(range1,range2))
			return 0;
	}
	return 1;
}
