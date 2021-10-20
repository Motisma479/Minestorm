#include "Math.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>

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
    else if(c.center.x > rect.max.x) distX = rect.max.x;

    if(c.center.y < rect.min.y) distX = rect.min.y;
    else if(c.center.y > rect.max.y) distY = rect.max.y;

    float distSq = lengthSqVector2d((Vector2d){distX,distY});

    return distSq <= c.radius * c.radius;
    
}


void drawShape()
{
    DrawPolyLines((Vector2){100.0f,200.0f},3,100.0f,0.0f,RED);
    Vector2d v1 = {2.5f,3.4f};
    Vector2d v2 = {2.51f,3.4f};
    printf("%d\n", isEqualToVector2d(v1,v2));
}


void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices)
{
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

Range getMinRange(Range r1, Range r2)
{
    Range r = {0.0f,0.0f};
    r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r2 : r1;

    return r; 
}

Range getMaxRange(Range r1, Range r2)
{
    Range r = {0.0f,0.0f};
    r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r1 : r2;
    
    return r; 
}

Range getPointProjOnVector(Vector2d vector, Vector2d point)
{
    Range r = {0.0f,0.0f};
    r.min = r.max = dotProduct(vector,point);

    return r;
}