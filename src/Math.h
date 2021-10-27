#pragma once
#include <math.h>
#include <stdbool.h>

#define EPSILON    pow(10,-9)

//2D vector
#ifndef RAYLIB_H
typedef struct Vector2 {
    float x;
    float y;
} Vector2;
#endif

//For SAT 
typedef struct Range
{
    float min;
    float max;
} Range;

//Line segment
typedef struct LineSegment
{
    Vector2 start;
    Vector2 end;

} LineSegment;

//Circle
typedef struct Circle
{
    Vector2 center;
    float radius;

} Circle;

//Rectangle
typedef struct AABB
{
    Vector2 min;
    Vector2 max;
    //Vector2 position;
    //Vector2 size;
} AABB;
//Oriented box
typedef struct OBB
{
    Vector2 start;
    Vector2 extends;
    float rotation;

} OBB;

typedef struct Triangle
{
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;

} Triangle;

//Convex Polygon
typedef struct ConvexPolygon
{
    int nbPoints;
    Vector2* points;

} ConvexPolygon;

//Union for store all polygon
typedef union Shapes
{
    Vector2 vector;
    LineSegment segment;
    AABB rectAB;
    OBB  rectOB;
    Triangle triangle;
    ConvexPolygon convexPoly;
    //Circle circle;

} Shapes;


//Type's of shape
//typedef enum ShapeType{POINT_SHAPE = 1,SEGMENT_SHAPE,AABB_SHAPE,
//OBB_SHAPE,TRIANGLE_SHAPE,CONVEX_SHAPE} ShapeType;
//OBB_SHAPE,TRIANGLE_SHAPE,CONVEX_SHAPE} ShapeType;

//Polygon
//typedef struct PolygonShape
//{
//ShapeType type;
//Shapes shapes;

//} PolygonShape;


//2D Vector functions
Vector2 zeroVector2();
Vector2 addVector2(Vector2 a,Vector2 b);
Vector2 subsVector2(Vector2 a,Vector2 b);
bool isEqualToVector2(Vector2 a,Vector2 b);
Vector2 normalizeVector2(Vector2 v);
Vector2 negateVector2(Vector2 v);

float lengthSqVector2(Vector2 v);
float lengthVector2(Vector2 v);
Vector2 getNormal(Vector2 a, Vector2 b);

Vector2 rotateAndTranslate(Vector2 vector, float rotation, Vector2 position);
Vector2 scaleVector2(Vector2 v,float scalar);
float distVector2(Vector2 a, Vector2 b);
float dotProduct(Vector2 a,Vector2 b);

//Some utilites fonctions
float lerp(float a,float b,float t);
float inverseLerp(float a,float b,float value);

//Collisions
Vector2 pointOnLineSegment(LineSegment segment, float t);
bool testPointRect(Vector2 point, AABB rect);
bool testPointCircle(Vector2 point,Circle c);
bool testRect(AABB r1,AABB r2);
bool testCircle(Circle c1,Circle c2);
bool testCircleRect(Circle c, AABB rect);


//Fonctions for the SAT
Vector2 getCenterConvexPoly(Vector2 *v, int size);
Range getPointProjOnVector(Vector2 vector, Vector2 point);
//void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices);
Range getMinRange(Range r1, Range r2);
Range getMaxRange(Range r1, Range r2);
bool rangeOverlapRange(Range r1, Range r2);


//bool intersect(PolygonShape shape1,int type1,PolygonShape shape2,int type2);
//void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices);

int satAlgorithm(Vector2 *a, Vector2 *b, int sizeA, int sizeB);
int satAlgorithmPolygonCircle(Vector2* v,int vSize,Circle* circle);