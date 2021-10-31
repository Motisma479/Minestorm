/* date = October 25th 2021 4:01 pm */

#ifndef COLLISION_H
#define COLLISION_H

#include "Math.h"
#include "game.h"

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

typedef struct MineLayerCollisionBox
{
	Vector2d poly[4];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
	Vector2d triangle3[3];
} MineLayerCollisionBox;

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

typedef struct MagneticFireCollisionBox
{
	Vector2d poly[4];
	Vector2d triangle1[3];
	Vector2d triangle2[3];
	Vector2d triangle3[3];
	Vector2d triangle4[3];
} MagneticFireCollisionBox;

MineLayerCollisionBox getMineLayerCollisionBox(float rotation, Vector2d position, float scale);
FloatingCollisionBox getFloatingCollisionBox(float rotation, Vector2d position, float scale);
MagneticCollisionBox getMagneticCollisionBox(float rotation, Vector2d position, float scale);
FireBallCollisionBox getFireBallCollisionBox(float rotation, Vector2d position, float scale);
MagneticFireCollisionBox getMagneticFireCollisionBox(float rotation,
													 Vector2d position,
													 float scale);
PlayerCollisionBox  getPlayerCollisionBox(float rotation, Vector2d position, float scale);

bool checkCollisionMineLayerBullet(MineLayerCollisionBox colBox,  Bullet bullet, char draw);
bool checkCollisionPlayerMineLayer(const PlayerCollisionBox colBox,
								   MineLayerCollisionBox magneticFire, char draw);
bool checkCollisionPlayerFloat(const PlayerCollisionBox player,  FloatingCollisionBox floating);
bool checkCollisionPlayerMagnetic(const PlayerCollisionBox player,  MagneticCollisionBox magnetic, char draw);
bool checkCollisionPlayerFireBall(const PlayerCollisionBox player,  FireBallCollisionBox fireball, char draw);
bool checkCollisionPlayerMagneticFire(const PlayerCollisionBox player,
									  MagneticFireCollisionBox magneticFire,
									  char draw);
bool checkCollisionPlayerBullet(const PlayerCollisionBox player,  Bullet bullet, char draw);
bool checkCollisionFloatBullet(FloatingCollisionBox floating,  Bullet *bullet, char draw);
bool checkCollisionFireBallBullet(FireBallCollisionBox fireball, Bullet *bullet, char draw);
bool checkCollisionMagneticBullet(MagneticCollisionBox magnetic, Bullet *bullet, char draw);
bool checkCollisionMagneticFireBullet(MagneticFireCollisionBox magnetic,
									  Bullet *bullet, char draw);

void drawShape(const Vector2d *v, int size,Color color);

#endif //COLLISION_H
