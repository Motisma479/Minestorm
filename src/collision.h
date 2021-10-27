/* date = October 25th 2021 4:01 pm */

#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"

typedef struct PlayerCollisionBox
{
	Vector2 head[6];
	Vector2 tail[8];
} PlayerCollisionBox;

typedef struct FloatingCollisionBox
{
	Vector2 rombus[4];
	Vector2 triangle1[3];
	Vector2 triangle2[3];
} FloatingCollisionBox;

typedef struct MagneticCollisionBox
{
	Vector2 poly[6];
	Vector2 triangle1[3];
	Vector2 triangle2[3];
} MagneticCollisionBox;

typedef struct FireBallCollisionBox
{
	Vector2 poly[7];
	Vector2 triangle1[3];
	Vector2 triangle2[3];
} FireBallCollisionBox;

typedef struct MagneticFireCollisionBox
{
	Vector2 poly[4];
	Vector2 triangle1[3];
	Vector2 triangle2[3];
	Vector2 triangle3[3];
	Vector2 triangle4[3];
} MagneticFireCollisionBox;

FloatingCollisionBox getFloatingCollisionBox(float rotation, Vector2 position, float scale);
MagneticCollisionBox getMagneticCollisionBox(float rotation, Vector2 position, float scale);
FireBallCollisionBox getFireBallCollisionBox(float rotation, Vector2 position, float scale);
MagneticFireCollisionBox getMagneticFireCollisionBox(float rotation,
													 Vector2 position,
													 float scale);
PlayerCollisionBox   getPlayerCollisionBox(float rotation, Vector2 position, float scale);
bool                 checkCollisionPlayerFloat(Player player,  FloatingCollisionBox floating, char draw);
bool                 checkCollisionPlayerMagnetic(Player player,  MagneticCollisionBox magnetic, char draw);
bool                 checkCollisionPlayerFireBall(Player player,  FireBallCollisionBox fireball, char draw);
bool                 checkCollisionPlayerMagneticFire(Player player,
													  MagneticFireCollisionBox magneticFire,
													  char draw);
bool                 checkCollisionFloatBullet(FloatingCollisionBox floating,  Bullet *bullet, char draw);
bool                 checkCollisionFireBallBullet(FireBallCollisionBox fireball, Bullet *bullet, char draw);
bool                 checkCollisionMagneticBullet(MagneticCollisionBox magnetic, Bullet *bullet, char draw);
bool                 checkCollisionMagneticFireBullet(MagneticFireCollisionBox magnetic,
													  Bullet *bullet, char draw);
void                 drawShape(Vector2 *v, int size,Color color);

#endif //COLLISION_H
