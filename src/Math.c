#include "Math.h"

/*
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
    return (a.x * b.x + a.y + b.y);
}

float lerp(float a,float b,float t)
{
    return (1.0f - t) * a + b * t;
}
float inverseLerp(float a,float b,float value)
{
    return (value - a) / (b - a);
}
Vector2d lerpVector2d(Vector2d a, Vector2d b, float t)
{
    
}
bool testPointRect(Vector2d point, Rectangle rect)
{

}
bool testRect(Rectangle r1,Rectangle r2)
{

}*/