#include "collision.h"

void drawShape(Vector2d *v, int size,Color color)
{
	int i = 0;
	for (i = 0;i < size - 1;i++)
		DrawLine(v[i].x, v[i].y, v[i+1].x, v[i+1].y, color);
	DrawLine(v[i].x, v[i].y, v[0].x, v[0].y, color);
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

MagneticFireBallCollisionBox getMagneticFireballCollisionBox(float rotation,
															 Vector2d position,
															 float scale)
{
	MagneticFireBallCollisionBox result = {
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

	int sizeHead = sizeof(result.head) / sizeof(Vector2d);
	int sizeTail = sizeof(result.tail) / sizeof(Vector2d);

	for (int i = 0; i < sizeHead;i++)
		head[i] = rotateAndTranslate(head[i], rotation, position);
	for (int i = 0; i < sizeTail;i++)
		tail[i] = rotateAndTranslate(tail[i], rotation, position);
	return (result);
}

bool checkCollisionPlayerFloat(Player player,  FloatingCollisionBox floating, char draw)
{
	PlayerCollisionBox playerCol = getPlayerCollisionBox(player.rotation, (Vector2d){player.position.x, player.position.y}, 0.25f);

	int sizeHead = sizeof(playerCol.head)     / sizeof(Vector2d);
	int sizeTail = sizeof(playerCol.tail)     / sizeof(Vector2d);
	int size1    = sizeof(floating.rombus)    / sizeof(Vector2d);
	int size2    = sizeof(floating.triangle1) / sizeof(Vector2d);
	int size3    = sizeof(floating.triangle2) / sizeof(Vector2d);

	Vector2d *head      = playerCol.head;
	Vector2d *tail      = playerCol.tail;
	Vector2d *rombus    = floating.rombus;
	Vector2d *triangle1 = floating.triangle1;
	Vector2d *triangle2 = floating.triangle2;

	int intersection1 =
		(satAlgorithm(head, rombus, sizeHead, size1) ||
		 satAlgorithm(tail, rombus, sizeTail, size1)) &&
		(satAlgorithm(rombus, head, size1, sizeHead) ||
		 satAlgorithm(rombus, tail, size1, sizeTail));


	int intersection2 =
		satAlgorithm(head, triangle1, sizeHead, size2) ||
		satAlgorithm(tail, triangle1, sizeTail, size2);

	int intersection3 =
		satAlgorithm(head, triangle2, sizeHead, size3) ||
		satAlgorithm(tail, triangle2, sizeTail, size3);

	if (draw)
	{
		drawShape(head, sizeHead, GREEN);
		drawShape(tail, sizeTail, GREEN);

		Color inter = intersection2 ? RED : GREEN;
		drawShape(triangle1, size2, inter);
		inter = intersection3 ? RED : GREEN;
		drawShape(triangle2, size3, inter);
		inter = intersection1 ? RED : GREEN;
		drawShape(rombus, size1, inter);
	}
	return (intersection1 || intersection2 || intersection3);
}

bool checkCollisionPlayerFireBall(Player player,  FireBallCollisionBox fireBall, char draw)
{
	PlayerCollisionBox colBox = getPlayerCollisionBox(player.rotation, (Vector2d){player.position.x, player.position.y}, 0.25f);

	int sizeHead = sizeof(colBox.head) / sizeof(Vector2d);
	int sizeTail = sizeof(colBox.tail) / sizeof(Vector2d);

	Vector2d *head = colBox.head;
	Vector2d *tail = colBox.tail;

	int size1 = sizeof(fireBall.poly)    / sizeof(Vector2d);
	int size2 = sizeof(fireBall.triangle1) / sizeof(Vector2d);
	int size3 = sizeof(fireBall.triangle2) / sizeof(Vector2d);

	Vector2d *poly    = fireBall.poly;
	Vector2d *triangle1 = fireBall.triangle1;
	Vector2d *triangle2 = fireBall.triangle2;

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

bool checkCollisionPlayerMagnetic(Player player,  MagneticCollisionBox magnetic, char draw)
{
	PlayerCollisionBox colBox = getPlayerCollisionBox(player.rotation, (Vector2d){player.position.x, player.position.y}, 0.25f);

	int sizeHead = sizeof(colBox.head) / sizeof(Vector2d);
	int sizeTail = sizeof(colBox.tail) / sizeof(Vector2d);

	Vector2d *head = colBox.head;
	Vector2d *tail = colBox.tail;

	int size1 = sizeof(magnetic.poly)    / sizeof(Vector2d);
	int size2 = sizeof(magnetic.triangle1) / sizeof(Vector2d);
	int size3 = sizeof(magnetic.triangle2) / sizeof(Vector2d);

	Vector2d *poly    = magnetic.poly;
	Vector2d *triangle1 = magnetic.triangle1;
	Vector2d *triangle2 = magnetic.triangle2;

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

bool checkCollisionPlayerMagneticFireBall(Player player,  MagneticFireBallCollisionBox magneticFire, char draw)
{
	PlayerCollisionBox colBox = getPlayerCollisionBox(player.rotation, (Vector2d){player.position.x, player.position.y}, 0.25f);

	int sizeHead = sizeof(colBox.head) / sizeof(Vector2d);
	int sizeTail = sizeof(colBox.tail) / sizeof(Vector2d);

	Vector2d *head = colBox.head;
	Vector2d *tail = colBox.tail;

	int size1 = sizeof(magneticFire.poly)      / sizeof(Vector2d);
	int size2 = sizeof(magneticFire.triangle1) / sizeof(Vector2d);
	int size3 = sizeof(magneticFire.triangle2) / sizeof(Vector2d);
	int size4 = sizeof(magneticFire.triangle3) / sizeof(Vector2d);
	int size5 = sizeof(magneticFire.triangle4) / sizeof(Vector2d);

	Vector2d *poly      = magneticFire.poly;
	Vector2d *triangle1 = magneticFire.triangle1;
	Vector2d *triangle2 = magneticFire.triangle2;
	Vector2d *triangle3 = magneticFire.triangle3;
	Vector2d *triangle4 = magneticFire.triangle4;

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
