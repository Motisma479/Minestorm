/* date = October 25th 2021 4:01 pm */

#ifndef COLLISION_H
#define COLLISION_H

#include "Math.h"
#include "player.h"

typedef struct PlayerCollisionBox
{
	Vector2d head[6];
	Vector2d tail[8];
} PlayerCollisionBox;

typedef struct FloatingCollisionBox
{
	Vector2d rombus[4];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
} FloatingCollisionBox;

typedef struct MagneticCollisionBox
{
	Vector2d poly[6];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
} MagneticCollisionBox;

typedef struct FireBallCollisionBox
{
	Vector2d poly[7];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
} FireBallCollisionBox;

typedef struct MagneticFireBallCollisionBox
{
	Vector2d poly[4];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
	Vector2d triangle3[3];
	Vector2d triangle4[3];

} MagneticFireBallCollisionBox;

FloatingCollisionBox getFloatingCollisionBox(float rotation, Vector2d position, float scale);
MagneticCollisionBox getMagneticCollisionBox(float rotation, Vector2d position, float scale);
FireBallCollisionBox getFireBallCollisionBox(float rotation, Vector2d position, float scale);
MagneticFireBallCollisionBox getMagneticFireballCollisionBox(float rotation,
															 Vector2d position,
															 float scale);
PlayerCollisionBox   getPlayerCollisionBox(float rotation, Vector2d position, float scale);
bool                 checkCollisionPlayerFloat(Player player,  FloatingCollisionBox floating, char draw);
bool                 checkCollisionPlayerMagnetic(Player player,  MagneticCollisionBox magnetic, char draw);
bool                 checkCollisionPlayerFireBall(Player player,  FireBallCollisionBox fireball, char draw);
bool                 checkCollisionPlayerMagneticFireBall(Player player,
														  MagneticFireBallCollisionBox magneticFire,
														  char draw);
void                 drawShape(Vector2d *v, int size,Color color);
MagneticFireBallCollisionBox getMagneticFireballCollisionBox(float rotation,
															 Vector2d position,
															 float scale);

#endif //COLLISION_H
