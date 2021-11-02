#include "Math.h"
#include <stdio.h>

Vector2d zeroVector2d()
{
    return (Vector2d){0.0f,0.0f};
}
Vector2d addVector2d(Vector2d a,Vector2d b)
{
    return (Vector2d){a.x + b.x, a.y + b.y};
}
Vector2d subsVector2d(Vector2d a,Vector2d b)
{
    return (Vector2d){a.x - b.x, a.y - b.y};
}
bool isEqualToVector2d(Vector2d a,Vector2d b)
{
    bool test = (a.x - b.x) >= -EPSILON  && (a.x - b.x) <= EPSILON && 
		(a.y - b.y) >= -EPSILON  && (a.y - b.y) <= EPSILON;

    return test;
}
Vector2d normalizeVector2d(Vector2d v)
{
    float length = lengthVector2d(v);
    if(length == 0.0f)
        return zeroVector2d();

    Vector2d vector;
    vector.x = v.x / length;
    vector.y = v.y / length;

    return vector;
}
Vector2d negateVector2d(Vector2d v)
{
    return (Vector2d){-v.x,-v.y};
}

Vector2d getDirection(float rotation)
{
    return (Vector2d){cosf(rotation*DEG2RAD),sinf(rotation*DEG2RAD)};
}

float getRotation(Vector2d direction)
{
    return (RAD2DEG * atan(direction.y / direction.x));
}

float lengthSqVector2d(Vector2d v)
{
    return (v.x*v.x + v.y*v.y);
}
float lengthVector2d(Vector2d v)
{
    return sqrtf(lengthSqVector2d(v));
}

Vector2d scaleVector2d(Vector2d v,float scalar)
{
    return (Vector2d){v.x * scalar, v.y * scalar};
}
float distVector2d(Vector2d a, Vector2d b)
{
    return lengthVector2d(subsVector2d(a,b));
}

float dotProduct(Vector2d a,Vector2d b)
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


Vector2d pointOnLineSegment(LineSegment segment, float t)
{
    Vector2d seg;
    seg.x = segment.start.x + subsVector2d(segment.start,segment.end).x * t;
    seg.y = segment.start.y + subsVector2d(segment.start,segment.end).y * t;

    return seg;
}
bool testPointCircle(Vector2d point,Circle c)
{
    float distSq =(distVector2d(point, c.center));
    distSq *= distSq;


    return distSq <= c.radius * c. radius;
}
bool testPointRect(Vector2d point, AABB rect)
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
    float distSq = distVector2d(c1.center,c2.center);
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

    float distSq = lengthSqVector2d((Vector2d){distX,distY});

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
			Vector2d* p1 = &shape.shapes.convexPoly.points[i];
			//Next vertex;
			Vector2d* p2 = &shape.shapes.convexPoly.points[ i + 1 == shape.shapes.convexPoly.nbPoints ? 0 : i+1 ];

			if(!isEqualToVector2d(*p1,*p2))
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
Vector2d getNormal(Vector2d a, Vector2d b)
{
	Vector2d result;

	result.x = -(b.y - a.y);
	result.y = (b.x - a.x);
	//result = normalizeVector2d(result);
	return (result);
}

Vector2d getLocalVector2d(Vector2d a, Vector2d b)
{
	Vector2d result = {b.x - a.x, b.y - a.y};

	return (result);
}

Vector2d rotateAndTranslate(Vector2d vector, float rotation, Vector2d position)
{
	Vector2d result = {
		.x = (vector.x * cosf(rotation) - vector.y*sinf(rotation)) + position.x,
		.y = (vector.x * sinf(rotation) + vector.y*cosf(rotation)) + position.y};
	return (result);
}

Vector2d getCenterConvexPoly(Vector2d *v, int size)
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

int satAlgorithm(const Vector2d *a,const Vector2d *b, int sizeA, int sizeB)
{
	float infinity = 1.0f / 0.0f;
	float minusInfinity = log(0);

	for (int i = 0; i < sizeA - 1;i++)
	{
		Range range1 = {infinity, minusInfinity};
		Range range2 = range1;

		Vector2d normal = getNormal(a[i], a[i + 1]);
		printf("normal x.%f y.%f x.%f y.%f %f %f\n",a[i].x, a[i].y, a[i+1].x, a[i+1].y, normal.x, normal.y);
		Vector2d absNormal = normal;
		Vector2d normalized = absNormal;
		if (absNormal.x < 0)
			absNormal.x = -absNormal.x;
		if (absNormal.y < 0)
			absNormal.y = -absNormal.y;
		absNormal.x += a[i].x;
		absNormal.y += a[i].y;
		//DrawLine(absNormal.x, absNormal.y, absNormal.x + (10*normalized.x), absNormal.y + (10*normalized.y), WHITE);
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

int satAlgorithmPolygonCircle(const Vector2d* v, int vSize, const Circle *circle)
{
	float infinity = 1.0f / 0.0f;
	float minusInfinity = log(0);

	for (int i = 0; i < vSize - 1;i++)
	{
		Range range1 = {infinity, minusInfinity};
		Range range2 = range1;

		Vector2d normal = getNormal(v[i], v[i + 1]);
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
			Vector2d normalized = normalizeVector2d(normal);


			float projection1 = dotProduct((Vector2d){circle->center.x + (normalized.x * circle->radius), circle->center.y + (normalized.y * circle->radius)}, normal);
			float projection2 = dotProduct((Vector2d){circle->center.x - (normalized.x * circle->radius), circle->center.y - (normalized.y * circle->radius)}, normal);

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
