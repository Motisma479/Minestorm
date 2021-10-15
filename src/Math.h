#pragma once
#include <math.h>
#include <stdbool.h>

#define EPSILON    pow(10,-9)

//2D vector
typedef struct Vector2d
{
    float x;
    float y;
     
} Vector2d;

//Line
typedef struct Line
{
    int nbPoints;
    Vector2d* points;

} Line;

//Line segment
typedef struct LineSegment
{
    Vector2d start;
    Vector2d end;

} LineSegment;

//Circle
typedef struct Circle
{
    Vector2d center;
    float radius;

} Circle;

//Rectangle
typedef struct Rectangle
{
    Vector2d min;
    Vector2d max;

} Rectangle;

//Oriented box
typedef struct OBB
{
    Vector2d start;
    Vector2d extends;
    float rotation;

} OBB;

//Convex Polygon
typedef struct ConvexPolygon
{
    int nbPoints;
    Vector2d* points;

} ConvexPolygon;

//2D Vector functions
Vector2d zeroVector2d();
Vector2d addVector2d(Vector2d a,Vector2d b);
Vector2d subsVector2d(Vector2d a,Vector2d b);
bool isEqualToVector2d(Vector2d a,Vector2d b);
Vector2d normalizeVector2d(Vector2d v);
Vector2d negateVector2d(Vector2d v);

float lengthSqVector2d(Vector2d v);
float lengthVector2d(Vector2d v);

Vector2d scaleVector2d(Vector2d v,float scalar);
float distVector2d(Vector2d a, Vector2d b);
float dotProduct(Vector2d a,Vector2d b);

//Collisions
bool testPointRect(Vector2d point, Rectangle rect);
bool testRect(Rectangle r1,Rectangle r2);

