#include "Math.h"
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

bool rangeOverlapRange(Range r1, Range r2)
{
    return (r1.min <= r2.max ) && (r2.min <= r1.max);
}

bool intersect(PolygonShape shape1,int type1,PolygonShape shape2,int type2)
{
    //to taste
    shape1.type = type1;//TRIANGLE_SHAPE;
    shape2.type = type2;//TRIANGLE_SHAPE;

    //To store the nomber of axis of shapes
    int nbAxis1 = 0;
    int nbAxis2 = 0;

    //Get the nomber of vertices, and put it in nbAxis1 and nbAxis2
    getNumberOfVertices(shape1,shape1.type,&nbAxis1);
    getNumberOfVertices(shape2,shape2.type,&nbAxis2);

    //Axis
    Vector2d axis1[nbAxis1];
    Vector2d axis2[nbAxis2];

    //Store the vertices of shapes
    Vector2d vertices1[nbAxis1];
    Vector2d vertices2[nbAxis2];

    //axis1
    Vector2d p11 = shape1.shapes.triangle.v1;
    Vector2d p12 = shape1.shapes.triangle.v2;
    Vector2d p13 = shape1.shapes.triangle.v3;

    vertices1[0] = p11;
    vertices1[1] = p11;
    vertices1[2] = p11;

    for(int i = 1; i < nbAxis1 - 1; i++)
    {
        Vector2d p1 = vertices1[i];
        Vector2d p2 = vertices1[i+1 == nbAxis1 ? 0 : i + 1];

        Vector2d edge = subsVector2d(p1,p2);

        Vector2d normal = {edge.y,-edge.x};

        Vector2d normalNormalized = normalizeVector2d(normal);

        axis1[i] = normalNormalized;
    }




    //axis2
    Vector2d p21 = shape2.shapes.triangle.v1;
    Vector2d p22 = shape2.shapes.triangle.v2;
    Vector2d p23 = shape2.shapes.triangle.v3;

    vertices2[0] = p21;
    vertices2[1] = p21;
    vertices2[2] = p23;


    for(int i = 0; i < nbAxis2; i++)
    {
        Vector2d p1 = vertices2[i];
        Vector2d p2 = vertices2[i+1 == nbAxis2 ? 0 : i + 1];

        Vector2d edge = subsVector2d(p1,p2);

        Vector2d normal = {edge.y,-edge.x};

        Vector2d normalNormalized = normalizeVector2d(normal);

        axis2[i] = normalNormalized;
    }


    //Loop over axis1
    //float min = dotProduct(axis1[0],vertices1[0]); //project vertex1 of shape1 onto axi1 of axis1
    //float max = min;
    for(int i = 0; i < nbAxis1; i++)
    {
        Vector2d axes = axis1[i];

        //project shape1 and shape2 onto axis1
        Range proj1 = getPointProjOnVector(axes,vertices1[i]);
        Range proj2 = getPointProjOnVector(axes,vertices1[i]);
    

        //TODO : test if projej1 don't overlap proj2 return false;
        if(!rangeOverlapRange(proj1,proj2))
        {
            return false;
        }
    }

    //Loop over axis2
    for(int i = 0; i < nbAxis2; i++)
    {
        Vector2d axes = axis2[i];

        //project shape1 and shape2 onto axis1
        //float proj1 = dotProduct(axes,vertices2[i]);
        //float proj2 = dotProduct(axes,vertices2[i]);
        Range proj1 = getPointProjOnVector(axes,vertices1[i]);
        Range proj2 = getPointProjOnVector(axes,vertices1[i]);

        //TODO : test if projej1 don't overlap proj2 return false;
        if(!rangeOverlapRange(proj1,proj2))
        {
            return false;
        }

    }

    return true;

}