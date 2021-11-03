#include "collision.h"

void drawShape(const Vector2d *v, int size, Color color)
{
	int i = 0;
	for (i = 0;i < size - 1;i++)
		DrawLine(v[i].x, v[i].y, v[i+1].x, v[i+1].y, color);
	DrawLine(v[i].x, v[i].y, v[0].x, v[0].y, color);
}

MineLayerCollisionBox getMineLayerCollisionBox(float rotation, Vector2d position, float scale)
{
	MineLayerCollisionBox result = {
		.poly = {{(-107.5 * scale) + position.x, (-14 * scale) + position.y}, 
			{(-107 * scale) + position.x, (14 * scale) + position.y}, 
			{(107 * scale) + position.x, (14 * scale) + position.y}, 
			{(107 * scale) + position.x, (-14 * scale) + position.y},
		},
		.triangle1 = {{(-107.5 * scale) + position.x, (-14 * scale) + position.y}, 
			{(-127.5 * scale) + position.x, (37 * scale) + position.y}, 
			{(-107.5 * scale) + position.x, (14 * scale) + position.y}, 
		},
		.triangle2 = {{(107.5 * scale) + position.x, (14 * scale) + position.y}, 
			{(127.5 * scale) + position.x, (37 * scale) + position.y}, 
			{(107.5 * scale) + position.x, (-14 * scale) + position.y}, 
		},
		.triangle3 = {{(-0.5 * scale) + position.x, (-41 * scale) + position.y}, 
			{(-34.5 * scale) + position.x, (-14 * scale) + position.y}, 
			{(34.5 * scale) + position.x, (-14 * scale) + position.y}, 
		}
	};
	return (result);
}

FloatingCollisionBox getFloatingCollisionBox(float rotation, Vector2d position, float scale)
{
	FloatingCollisionBox result = {
		.rombus = {
			{(-9.215851  * scale) + position.x, (-111.811523 * scale) + position.y},
			{(-27.215851 * scale) + position.x, (-52.811523  * scale) + position.y},
			{(-9.215851  * scale) + position.x, (-16.811523  * scale) + position.y},
			{(8.784149   * scale) + position.x, (-52.811523  * scale) + position.y}},
		.triangle1 = {
			{(-27.215851 * scale) + position.x, (-52.811523 * scale) + position.y},
			{(-66.215851 * scale) + position.x, (-3.811523  * scale) + position.y},
			{(-9.215851  * scale) + position.x, (-16.811523 * scale) + position.y}},
		.triangle2 = {
			{(-9.215851 * scale) + position.x, (-16.811523 * scale) + position.y},
			{(48.784149 * scale) + position.x, (-3.811523  * scale) + position.y},
			{(8.784149  * scale) + position.x, (-52.811523 * scale) + position.y}}
	};
	return (result);
}

MagneticCollisionBox getMagneticCollisionBox(float rotation, Vector2d position, float scale)
{

	MagneticCollisionBox result = {
		.poly = {
			{(43.956299  * scale) + position.x, (65.256317  * scale) + position.y},
			{(19.956299  * scale) + position.x, (117.256317 * scale) + position.y},
			{(68.956299  * scale) + position.x, (91.256317  * scale) + position.y},
			{(94.956299  * scale) + position.x, (65.256317  * scale) + position.y},
			{(117.956299 * scale) + position.x, (14.256317  * scale) + position.y},
			{(68.956299  * scale) + position.x, (39.256317  * scale) + position.y},
		},
		.triangle1 = {
			{(68.956299 * scale) + position.x, (39.256317 * scale) + position.y},
			{(20.956299 * scale) + position.x, (17.256317 * scale) + position.y},
			{(43.956299 * scale) + position.x, (65.256317 * scale) + position.y}, 
		},
		.triangle2 = {
			{(68.956299  * scale) + position.x, (91.256317  * scale) + position.y},
			{(116.956299 * scale) + position.x, (113.256317 * scale) + position.y},
			{(94.956299  * scale) + position.x, (65.256317  * scale) + position.y},
		}

	};

	return (result);
}

FireBallCollisionBox getFireBallCollisionBox(float rotation, Vector2d position, float scale)
{
	FireBallCollisionBox result = {
		.poly = {
			{(-12.904968 * scale) + position.x, (-46.521027 * scale) + position.y}, 
			{(-64.904968 * scale) + position.x, (-59.521027 * scale) + position.y}, 
			{(-52.904968 * scale) + position.x, (-7.521027  * scale) + position.y}, 
			{(-12.904968 * scale) + position.x, (32.478973  * scale) + position.y}, 
			{(38.095032  * scale) + position.x, (45.478973  * scale) + position.y}, 
			{(25.095032  * scale) + position.x, (-8.521027  * scale) + position.y}, 
			{(-16.904968 * scale) + position.x, (-47.521027 * scale) + position.y}}, 
		.triangle1 = {
			{(-52.904968 * scale) + position.x, (-7.521027 * scale) + position.y}, 
			{(-64.904968 * scale) + position.x, (45.478973 * scale) + position.y}, 
			{(-12.904968 * scale) + position.x, (32.478973 * scale) + position.y}}, 
		.triangle2 = {
			{(25.095032  * scale) + position.x, (-8.521027  * scale) + position.y}, 
			{(38.095032  * scale) + position.x, (-59.521027 * scale) + position.y}, 
			{(-16.904968 * scale) + position.x, (-47.521027 * scale) + position.y}}, 
	};
	return (result);
}

MagneticFireCollisionBox getMagneticFireCollisionBox(float rotation,
													 Vector2d position,
													 float scale)
{
	MagneticFireCollisionBox result = {
		.poly = {
			{(-43.000000 * scale) + position.x, (-45.000000 * scale) + position.y}, 
			{(-43.000000 * scale) + position.x, (45.000000  * scale) + position.y}, 
			{(44.000000  * scale) + position.x, (45.000000  * scale) + position.y}, 
			{(44.000000  * scale) + position.x, (-45.000000 * scale) + position.y}, 
		},
		.triangle1 = {
			{(-30.000000 * scale) + position.x, (-45.000000 * scale) + position.y}, 
			{(-43.000000 * scale) + position.x, (-76.000000 * scale) + position.y}, 
			{(-43.000000 * scale) + position.x, (-45.000000 * scale) + position.y},
		},
		.triangle2 = {
			{(-43.000000 * scale) + position.x, (32.000000 * scale) + position.y}, 
			{(-73.000000 * scale) + position.x, (45.000000 * scale) + position.y}, 
			{(-43.000000 * scale) + position.x, (45.000000 * scale) + position.y}, 
		},
		.triangle3 = {
			{(32.000000 * scale) + position.x, (45.000000 * scale) + position.y}, 
			{(44.000000 * scale) + position.x, (76.000000 * scale) + position.y}, 
			{(44.000000 * scale) + position.x, (45.000000 * scale) + position.y}, 
		},
		.triangle4 = {
			{(44.000000 * scale) + position.x, (-32.000000 * scale) + position.y}, 
			{(75.000000 * scale) + position.x, (-45.000000 * scale) + position.y}, 
			{(44.000000 * scale) + position.x, (-45.000000 * scale) + position.y}, 
		}
	};
	return (result);
}

PlayerCollisionBox getPlayerCollisionBox(float rotation, Vector2d position, float scale)
{
	rotation += 90.0f;
	rotation *= DEG2RAD;
	PlayerCollisionBox result = {
		.head = {
			{(-0.371109  * scale), (-87.404861 * scale)},
			{(-17.371109 * scale), (-46.404861 * scale)},
			{(-13.371109 * scale), (-15.404861 * scale)},
			{(15.628891  * scale), (-15.404861 * scale)},
			{(19.628891  * scale), (-46.404861 * scale)},
			{(2.628891   * scale), (-87.404861 * scale)}},
		.tail = {
			{(-13.371109 * scale), (-15.404861 * scale)},
			{(-29.371109 * scale), (-15.404861 * scale)},
			{(-40.371109 * scale), (32.595139  * scale)},
			{(-30.371109 * scale), (51.595139  * scale)},
			{(32.628891  * scale), (51.595139  * scale)},
			{(42.628891  * scale), (32.595139  * scale)},
			{(26.628891  * scale), (-15.404861 * scale)},
			{(15.628891  * scale), (-15.404861 * scale)}}
	};

	Vector2d *head = result.head;
	Vector2d *tail = result.tail;

	int sizeHead = ARRAY_SIZE(result.head);
	int sizeTail = ARRAY_SIZE(result.tail);

	for (int i = 0; i < sizeHead;i++)
		head[i] = rotateAndTranslate(head[i], rotation, position);
	for (int i = 0; i < sizeTail;i++)
		tail[i] = rotateAndTranslate(tail[i], rotation, position);
	return (result);
}


bool checkCollisionPlayerMineLayer(const PlayerCollisionBox colBox,
								   MineLayerCollisionBox magneticFire, char draw)
{
	int sizeHead = ARRAY_SIZE(colBox.head);
	int sizeTail = ARRAY_SIZE(colBox.tail);

	const Vector2d *head = colBox.head;
	const Vector2d *tail = colBox.tail;

	int size1 = ARRAY_SIZE(magneticFire.poly);
	int size2 = ARRAY_SIZE(magneticFire.triangle1);
	int size3 = ARRAY_SIZE(magneticFire.triangle2);
	int size4 = ARRAY_SIZE(magneticFire.triangle3);

	const Vector2d *poly      = magneticFire.poly;
	const Vector2d *triangle1 = magneticFire.triangle1;
	const Vector2d *triangle2 = magneticFire.triangle2;
	const Vector2d *triangle3 = magneticFire.triangle3;

	int intersection1 =
		(satAlgorithm(head, poly, sizeHead, size1) ||
		 satAlgorithm(tail, poly, sizeTail, size1)) &&
		(satAlgorithm(poly, head, size1, sizeHead) ||
		 satAlgorithm(poly, tail, size1, sizeTail));

	int intersection2 =
		(satAlgorithm(head, triangle1, sizeHead, size2) ||
		 satAlgorithm(tail, triangle1, sizeTail, size2)) &&
		(satAlgorithm(triangle1, head, size2, sizeHead) ||
		 satAlgorithm(triangle1, tail, size2, sizeTail));

	int intersection3 =
		(satAlgorithm(head, triangle2, sizeHead, size3) ||
		 satAlgorithm(tail, triangle2, sizeTail, size3)) &&
		(satAlgorithm(triangle2, head, size3, sizeHead) ||
		 satAlgorithm(triangle2, tail, size3, sizeTail));

	int intersection4 =
		(satAlgorithm(head, triangle3, sizeHead, size4) ||
		 satAlgorithm(tail, triangle3, sizeTail, size4)) &&
		(satAlgorithm(triangle3, head, size4, sizeHead) ||
		 satAlgorithm(triangle3, tail, size4, sizeTail));

	if (draw)
	{
		Color inter;

		drawShape(head, sizeHead, GREEN);
		drawShape(tail, sizeTail, GREEN);

		inter = intersection1 ? RED : GREEN;
		drawShape(poly, size1, inter);
		inter = intersection2 ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		inter = intersection3 ? RED : GREEN;
		drawShape(triangle2, size3, inter);
		inter = intersection4 ? RED : GREEN;
		drawShape(triangle3, size4, inter);
	}
	return (intersection1 || intersection2 || intersection3 ||
			intersection4);
}

bool checkCollisionPlayerFloat(const PlayerCollisionBox playerCol,  FloatingCollisionBox floating)
{

	int sizeHead = ARRAY_SIZE(playerCol.head);
	int sizeTail = ARRAY_SIZE(playerCol.tail);
	int size1    = ARRAY_SIZE(floating.rombus);
	int size2    = ARRAY_SIZE(floating.triangle1);
	int size3    = ARRAY_SIZE(floating.triangle2);

	const Vector2d *head      = playerCol.head;
	const Vector2d *tail      = playerCol.tail;
	const Vector2d *rombus    = floating.rombus;
	const Vector2d *triangle1 = floating.triangle1;
	const Vector2d *triangle2 = floating.triangle2;

	int intersection =
		((satAlgorithm(head, rombus, sizeHead, size1) ||
		  satAlgorithm(tail, rombus, sizeTail, size1)) &&
		 (satAlgorithm(rombus, head, size1, sizeHead) ||
		  satAlgorithm(rombus, tail, size1, sizeTail))) || 
		satAlgorithm(head, triangle1, sizeHead, size2) ||
		satAlgorithm(tail, triangle1, sizeTail, size2) || 
		satAlgorithm(head, triangle2, sizeHead, size3) ||
		satAlgorithm(tail, triangle2, sizeTail, size3);

	return (intersection);
}

bool checkCollisionPlayerFireBall(const PlayerCollisionBox colBox,  FireBallCollisionBox fireBall, char draw)
{
	int sizeHead = ARRAY_SIZE(colBox.head);
	int sizeTail = ARRAY_SIZE(colBox.tail);

	const Vector2d *head = colBox.head;
	const Vector2d *tail = colBox.tail;

	int size1 = ARRAY_SIZE(fireBall.poly);
	int size2 = ARRAY_SIZE(fireBall.triangle1);
	int size3 = ARRAY_SIZE(fireBall.triangle2);

	const Vector2d *poly    = fireBall.poly;
	const Vector2d *triangle1 = fireBall.triangle1;
	const Vector2d *triangle2 = fireBall.triangle2;

	int intersection1 =
		(satAlgorithm(head, poly, sizeHead, size1) ||
		 satAlgorithm(tail, poly, sizeTail, size1)) &&
		(satAlgorithm(poly, head, size1, sizeHead) ||
		 satAlgorithm(poly, tail, size1, sizeTail));

	int intersection2 =
		(satAlgorithm(head, triangle1, sizeHead, size2) ||
		 satAlgorithm(tail, triangle1, sizeTail, size2)) &&
		(satAlgorithm(triangle1, head, size2, sizeHead) ||
		 satAlgorithm(triangle1, tail, size2, sizeTail));

	int intersection3 =
		(satAlgorithm(head, triangle2, sizeHead, size3) ||
		 satAlgorithm(tail, triangle2, sizeTail, size3)) &&
		(satAlgorithm(triangle2, head, size3, sizeHead) ||
		 satAlgorithm(triangle2, tail, size3, sizeTail));

	if (draw)
	{
		Color inter;

		drawShape(head, sizeHead, GREEN);
		drawShape(tail, sizeTail, GREEN);

		inter = intersection1 ? RED : GREEN;
		drawShape(poly, size1, inter);
		inter = intersection2 ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		inter = intersection3 ? RED : GREEN;
		drawShape(triangle2, size3, inter);
	}
	return (intersection1 || intersection2 || intersection3);
}

bool checkCollisionPlayerMagnetic(const PlayerCollisionBox colBox,  MagneticCollisionBox magnetic, char draw)
{
	int sizeHead = ARRAY_SIZE(colBox.head);
	int sizeTail = ARRAY_SIZE(colBox.tail);

	const Vector2d *head = colBox.head;
	const Vector2d *tail = colBox.tail;

	int size1 = ARRAY_SIZE(magnetic.poly);
	int size2 = ARRAY_SIZE(magnetic.triangle1);
	int size3 = ARRAY_SIZE(magnetic.triangle2);

	const Vector2d *poly    = magnetic.poly;
	const Vector2d *triangle1 = magnetic.triangle1;
	const Vector2d *triangle2 = magnetic.triangle2;

	int intersection1 =
		(satAlgorithm(head, poly, sizeHead, size1) ||
		 satAlgorithm(tail, poly, sizeTail, size1)) &&
		(satAlgorithm(poly, head, size1, sizeHead) ||
		 satAlgorithm(poly, tail, size1, sizeTail));

	int intersection2 =
		(satAlgorithm(head, triangle1, sizeHead, size2) ||
		 satAlgorithm(tail, triangle1, sizeTail, size2)) &&
		(satAlgorithm(triangle1, head, size2, sizeHead) ||
		 satAlgorithm(triangle1, tail, size2, sizeTail));

	int intersection3 =
		(satAlgorithm(head, triangle2, sizeHead, size3) ||
		 satAlgorithm(tail, triangle2, sizeTail, size3)) &&
		(satAlgorithm(triangle2, head, size3, sizeHead) ||
		 satAlgorithm(triangle2, tail, size3, sizeTail));


	if (draw)
	{
		Color inter;

		drawShape(head, sizeHead, GREEN);
		drawShape(tail, sizeTail, GREEN);

		inter = intersection1 ? RED : GREEN;
		drawShape(poly, size1, inter);
		inter = intersection2 ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		inter = intersection3 ? RED : GREEN;
		drawShape(triangle2, size3, inter);
	}
	return (intersection1 || intersection2 || intersection3);
}

bool checkCollisionPlayerMagneticFire(const PlayerCollisionBox colBox,  MagneticFireCollisionBox magneticFire, char draw)
{
	int sizeHead = ARRAY_SIZE(colBox.head);
	int sizeTail = ARRAY_SIZE(colBox.tail);

	const Vector2d *head = colBox.head;
	const Vector2d *tail = colBox.tail;

	int size1 = ARRAY_SIZE(magneticFire.poly);
	int size2 = ARRAY_SIZE(magneticFire.triangle1);
	int size3 = ARRAY_SIZE(magneticFire.triangle2);
	int size4 = ARRAY_SIZE(magneticFire.triangle3);
	int size5 = ARRAY_SIZE(magneticFire.triangle4);

	const Vector2d *poly      = magneticFire.poly;
	const Vector2d *triangle1 = magneticFire.triangle1;
	const Vector2d *triangle2 = magneticFire.triangle2;
	const Vector2d *triangle3 = magneticFire.triangle3;
	const Vector2d *triangle4 = magneticFire.triangle4;

	int intersection1 =
		(satAlgorithm(head, poly, sizeHead, size1) ||
		 satAlgorithm(tail, poly, sizeTail, size1)) &&
		(satAlgorithm(poly, head, size1, sizeHead) ||
		 satAlgorithm(poly, tail, size1, sizeTail));

	int intersection2 =
		(satAlgorithm(head, triangle1, sizeHead, size2) ||
		 satAlgorithm(tail, triangle1, sizeTail, size2)) &&
		(satAlgorithm(triangle1, head, size2, sizeHead) ||
		 satAlgorithm(triangle1, tail, size2, sizeTail));

	int intersection3 =
		(satAlgorithm(head, triangle2, sizeHead, size3) ||
		 satAlgorithm(tail, triangle2, sizeTail, size3)) &&
		(satAlgorithm(triangle2, head, size3, sizeHead) ||
		 satAlgorithm(triangle2, tail, size3, sizeTail));

	int intersection4 =
		(satAlgorithm(head, triangle3, sizeHead, size4) ||
		 satAlgorithm(tail, triangle3, sizeTail, size4)) &&
		(satAlgorithm(triangle3, head, size4, sizeHead) ||
		 satAlgorithm(triangle3, tail, size4, sizeTail));

	int intersection5 =
		(satAlgorithm(head, triangle4, sizeHead, size5) ||
		 satAlgorithm(tail, triangle4, sizeTail, size5)) &&
		(satAlgorithm(triangle4, head, size5, sizeHead) ||
		 satAlgorithm(triangle4, tail, size5, sizeTail));

	if (draw)
	{
		Color inter;

		drawShape(head, sizeHead, GREEN);
		drawShape(tail, sizeTail, GREEN);

		inter = intersection1 ? RED : GREEN;
		drawShape(poly, size1, inter);

		inter = intersection2 ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		inter = intersection3 ? RED : GREEN;
		drawShape(triangle2, size3, inter);
		inter = intersection4 ? RED : GREEN;
		drawShape(triangle3, size4, inter);
		inter = intersection5 ? RED : GREEN;
		drawShape(triangle4, size5, inter);
	}
	return (intersection1 || intersection2 || intersection3 ||
			intersection4 || intersection5);
}

bool checkCollisionMineLayerBullet(MineLayerCollisionBox colBox,  Bullet bullet, char draw)
{
	Circle circle = {{bullet.position.x, bullet.position.y}, 6.25f / 2};
	int sizePoly = ARRAY_SIZE(colBox.poly);
	int size1 = ARRAY_SIZE(colBox.triangle1);
	int size2 = ARRAY_SIZE(colBox.triangle2);
	int size3 = ARRAY_SIZE(colBox.triangle3);

	const Vector2d *poly = colBox.poly;
	const Vector2d *triangle1 = colBox.triangle1;
	const Vector2d *triangle2 = colBox.triangle2;
	const Vector2d *triangle3 = colBox.triangle3;

	int intersection = satAlgorithmPolygonCircle(poly, size1, &circle) ||
		satAlgorithmPolygonCircle(triangle1, size2, &circle) ||
		satAlgorithmPolygonCircle(triangle2, size3, &circle);

	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(poly, sizePoly, inter);
		drawShape(triangle1, size1, inter);
		drawShape(triangle2, size2, inter);
		drawShape(triangle3, size3, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}

bool checkCollisionPlayerBullet(const PlayerCollisionBox colBox,  Bullet bullet, char draw)
{
	Circle circle = {{bullet.position.x, bullet.position.y}, 6.25f / 2};
	int sizeHead = ARRAY_SIZE(colBox.head);
	int sizeTail = ARRAY_SIZE(colBox.tail);

	const Vector2d *head = colBox.head;
	const Vector2d *tail = colBox.tail;

	int intersection = satAlgorithmPolygonCircle(head, sizeHead, &circle) ||
		satAlgorithmPolygonCircle(tail, sizeTail, &circle);
	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(head, sizeHead, inter);
		drawShape(tail, sizeTail, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}

bool checkCollisionFloatBullet(FloatingCollisionBox floating,  Bullet *bullet, char draw)
{
	Circle circle = {{bullet->position.x, bullet->position.y}, 6.25f / 2};
	int size1    = ARRAY_SIZE(floating.rombus);
	int size2    = ARRAY_SIZE(floating.triangle1);
	int size3    = ARRAY_SIZE(floating.triangle2);

	const Vector2d *rombus    = floating.rombus;
	const Vector2d *triangle1 = floating.triangle1;
	const Vector2d *triangle2 = floating.triangle2;

	int intersection = satAlgorithmPolygonCircle(rombus, size1, &circle) ||
		satAlgorithmPolygonCircle(triangle1, size2, &circle) || satAlgorithmPolygonCircle(triangle2, size3, &circle);
	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		drawShape(triangle2, size3, inter);
		drawShape(rombus, size1, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}

bool checkCollisionFireBallBullet(FireBallCollisionBox fireball, Bullet *bullet, char draw)
{
	Circle circle = {{bullet->position.x, bullet->position.y}, 6.25f / 2};
	int size1    = ARRAY_SIZE(fireball.poly);
	int size2    = ARRAY_SIZE(fireball.triangle1);
	int size3    = ARRAY_SIZE(fireball.triangle2);

	const Vector2d *rombus    = fireball.poly;
	const Vector2d *triangle1 = fireball.triangle1;
	const Vector2d *triangle2 = fireball.triangle2;

	int intersection = satAlgorithmPolygonCircle(rombus, size1, &circle) ||
		satAlgorithmPolygonCircle(triangle1, size2, &circle) || satAlgorithmPolygonCircle(triangle2, size3, &circle);
	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		drawShape(triangle2, size3, inter);
		drawShape(rombus, size1, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}

bool checkCollisionMagneticBullet(MagneticCollisionBox magnetic, Bullet *bullet, char draw)
{
	Circle circle = {{bullet->position.x, bullet->position.y}, 6.25f / 2};
	int size1    = ARRAY_SIZE(magnetic.poly);
	int size2    = ARRAY_SIZE(magnetic.triangle1);
	int size3    = ARRAY_SIZE(magnetic.triangle2);

	const Vector2d *rombus    = magnetic.poly;
	const Vector2d *triangle1 = magnetic.triangle1;
	const Vector2d *triangle2 = magnetic.triangle2;

	int intersection = satAlgorithmPolygonCircle(rombus, size1, &circle) ||
		satAlgorithmPolygonCircle(triangle1, size2, &circle) || satAlgorithmPolygonCircle(triangle2, size3, &circle);
	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		drawShape(triangle2, size3, inter);
		drawShape(rombus, size1, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}

bool checkCollisionMagneticFireBullet(MagneticFireCollisionBox magnetic, Bullet *bullet, char draw)
{
	Circle circle = {{bullet->position.x, bullet->position.y}, 6.25f / 2};
	int size1    = ARRAY_SIZE(magnetic.poly);
	int size2    = ARRAY_SIZE(magnetic.triangle1);
	int size3    = ARRAY_SIZE(magnetic.triangle2);

	const Vector2d *rombus    = magnetic.poly;
	const Vector2d *triangle1 = magnetic.triangle1;
	const Vector2d *triangle2 = magnetic.triangle2;

	int intersection = satAlgorithmPolygonCircle(rombus, size1, &circle) ||
		satAlgorithmPolygonCircle(triangle1, size2, &circle) || satAlgorithmPolygonCircle(triangle2, size3, &circle);
	if (draw)
	{
		Color inter;

		inter = intersection ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		drawShape(triangle2, size3, inter);
		drawShape(rombus, size1, inter);
		DrawCircle(circle.center.x, circle.center.y, circle.radius, WHITE);
	}
	return (intersection);
}
