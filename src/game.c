#include "game.h"
#include "draw.h"
#include "collision.h"
#include "levels.h"
#include "player.h"

int addEnemy(Game *game, EnemySize size, EnemyType type)
{
	for (int i = 0; i < game->enemyCount;i++)
	{
		Enemy *enemy = &game->enemies[i];
		if (!enemy->active)
		{
			initEnemy(enemy, enemy->position, type, size);
			enemy->active = true;
			return (1);
		}
	}
	return (0);
}

void updateGame(Game* game)
{
	if (game->highScore < game->player[0].score)
		game->highScore = game->player[0].score;
	if (game->highScore < game->player[1].score)
		game->highScore = game->player[1].score;
	switch(game->state)
	{
		case GS_MENU:{
			if (game->player[1].action & PA_SHOOT)
			{
				game->state = GS_PLAY;
				game->twoPlayers = true;
			}
			else if (game->player[0].action & PA_SHOOT)
				game->state = GS_PLAY;
			game->player[0].action &= ~(PA_SHOOT);
			game->player[1].action &= ~(PA_SHOOT);
		}break;
		case GS_PLAY:{
			if (game->levelStart == false)
			{
				if (updateLayer(&game->layer, game->ticksCount))
				{
					game->levelStart = true;
					startLevel(game);
				}
			}
			else
			{
				updatePlayer(&game->player[0], game->ticksCount);
				if (game->player[0].action & PA_SHOOT)
					gameAddBullet(game, BS_PLAYER1, NULL);
				if (game->twoPlayers)
				{
					updatePlayer(&game->player[1], game->ticksCount);
					if (game->player[1].action & PA_SHOOT)
						gameAddBullet(game, BS_PLAYER2, NULL);
				}
				for(int i = 0; i < game->bulletCount; i++)
				{
					Bullet* bullet = &game->bullets[i];
					updateBullet(bullet,game->ticksCount);
					if (bullet->source == BS_PLAYER1)
						drawBullet(bullet, game->atlas, BLUE);
					if (bullet->source == BS_PLAYER2)
						drawBullet(bullet, game->atlas, GREEN);
					if (bullet->source == BS_ENEMY)
						drawBullet(bullet, game->atlas, RED);
				}

				for(int i = 0; i < game->enemyCount; i++)
					updateEnemy(game, &game->enemies[i], game->ticksCount, &game->player[0], &game->player[1]);
				gameCollisions(game);
				gameRemoveBullet(game);
				gameIsOver(game);
			}
		} break;
		default:;
	}
}

static void gameAddEnemyBullet(Game *game, Enemy *enemy)
{
	Vector2d position;
	float   angle;
	float speed = 100.0f;
	Vector2d direction = subsVector2d(game->player[0].position, enemy->position);
	Vector2d direction1 = subsVector2d(game->player[1].position, enemy->position);

	if (lengthVector2d(direction) > lengthVector2d(direction1))
		direction = direction1;

	direction = normalizeVector2d(direction);
	if (enemy->size == ES_BIG)
	{
		direction.x *= 40;
		direction.y *= 40;
	}
	else if (enemy->size == ES_MEDIUM)
	{
		direction.x *= 30;
		direction.y *= 30;
	}
	else
	{
		direction.x *= 20;
		direction.y *= 20;
	}
	position.x = enemy->position.x + direction.x;
	position.y = enemy->position.y + direction.y;
	angle = getRotation(direction);
	if (direction.x < 0)
		angle += 180.0f;
	Bullet bullet = {0};

	if (!enemy->shot)
	{
		initBullet(&bullet, position, angle, BS_ENEMY, speed);
		enemy->shot = true;
	}
	game->bullets[game->bulletCount] = bullet;
	game->bulletCount += 1;
}

void gameAddBullet(Game *game, BulletSource source, Enemy *enemy)
{
	if(game->bulletCount == BULLET_CAPACITY)
		return;
	switch(source)
	{
		case BS_PLAYER1:
		case BS_PLAYER2:
		{

			float speed = 900.0f;

			Player *player = &game->player[0];
			if (source == BS_PLAYER2)
				player = &game->player[1];

			player->action &= ~(PA_SHOOT);
			Vector2d direction = getDirection(player->rotation);
			Vector2d position;
			position.x  = player->position.x + (direction.x * 25);
			position.y  = player->position.y + (direction.y * 25);
			float angle = player->rotation;

			Bullet bullet = {0};
			initBullet(&bullet, position, angle, source, speed);
			game->bullets[game->bulletCount] = bullet;
			game->bulletCount += 1;
		}break;
		case BS_ENEMY:gameAddEnemyBullet(game, enemy);break;
	}
}

void gameRemoveBullet(Game *game)
{
	for(int i = 0; i < game->bulletCount; i++)
	{
		Bullet* bullet = &game->bullets[i];

		if ((bullet->source != BS_ENEMY && bullet->lifeTime > 0.7f) ||
			(bullet->source == BS_ENEMY && bullet->lifeTime > 7.0f))
		{
			game->bullets[i] = game->bullets[game->bulletCount - 1];
			game->bulletCount -= 1;
		}
	}
}

void addScore(Game *game, BulletSource source, EnemySize size, EnemyType type, int score)
{
	Player stub;
	Player *player = &stub;

	if (source == BS_PLAYER1)
		player = &game->player[0];
	else if (source == BS_PLAYER2)
		player = &game->player[1];
	switch(size)
	{
		case ES_MEDIUM:
		case ES_BIG:
		{
			addEnemy(game, size - 1, type);
			addEnemy(game, size - 1, type);
		}break;
		default:;
	}
	player->score += score;
}

int collisionEnemyBullet(Game *game, Enemy *enemy, Bullet *bullet)
{
	if (enemy->active && enemy->type != ET_NONE)
	{
		switch (enemy->type)
		{
			case ET_FLOATING:{
				FloatingCollisionBox floating =
					getFloatingCollisionBox(0, enemy->position, enemy->scale);
				if (checkCollisionFloatBullet(floating, bullet, game->draw))
				{
					addScore(game, bullet->source, enemy->size, enemy->type, enemy->pointsToRecieve);
					return (1);
				}
			}break;

			case ET_FIREBALL:{
				FireBallCollisionBox fireball =
					getFireBallCollisionBox(0, enemy->position, enemy->scale);
				if (checkCollisionFireBallBullet(fireball, bullet, game->draw))
				{
					addScore(game, bullet->source, enemy->size, enemy->type, enemy->pointsToRecieve);
					gameAddBullet(game, BS_ENEMY, enemy);
					return (1);
				}
			}break;

			case ET_MAGNETIC:{
				MagneticCollisionBox magnetic =
					getMagneticCollisionBox(0, enemy->position, enemy->scale);
				if (checkCollisionMagneticBullet(magnetic, bullet,
												 game->draw))
				{
					addScore(game, bullet->source, enemy->size, enemy->type, enemy->pointsToRecieve);
					return (1);
				}
			}break;
			case ET_MAGNETIC_FIREBALL:{
				MagneticFireCollisionBox magneticFire =
					getMagneticFireCollisionBox(0, enemy->position, enemy->scale);
				if (checkCollisionMagneticFireBullet(magneticFire, bullet,
													 game->draw))
				{
					addScore(game, bullet->source, enemy->size, enemy->type, enemy->pointsToRecieve);
					gameAddBullet(game, BS_ENEMY, enemy);
					return (1);
				}
			}break;
			case ET_MINE_LAYER:{
				MineLayerCollisionBox mineLayer =
					getMineLayerCollisionBox(0, enemy->position, enemy->scale);
				if (checkCollisionMineLayerBullet(mineLayer, *bullet,
												  game->draw))
				{
					if (bullet->source == BS_PLAYER1)
						game->player[0].score += 1000;
					else if (bullet->source == BS_PLAYER2)
						game->player[1].score += 1000;
					return (1);
				}
			}break;
			default:;
		}
	}
	return (0);
}

static void bulletBulletCollisions(Game *game, bool *player1Hit, bool *player2Hit, PlayerCollisionBox *player1, PlayerCollisionBox *player2)
{
	for(int i = 0; i < game->bulletCount; i++)
	{
		Bullet* bullet = &game->bullets[i];
		for(int j = i + 1; j < game->bulletCount; j++)
		{
			Bullet* bullet1 = &game->bullets[j];

			float distance  = distVector2d(bullet1->position, bullet->position);
			if (distance <= 6.25f)
			{
				bullet->lifeTime = 1000.0f;
				bullet1->lifeTime = 1000.0f;
				if (bullet->source != BS_ENEMY)
				{
					if (bullet->source == BS_PLAYER1)
						game->player[0].score += 100;
					else
						game->player[1].score += 100;

				}
				if (bullet1->source != BS_ENEMY)
				{
					if (bullet1->source == BS_PLAYER1)
						game->player[0].score += 100;
					else
						game->player[1].score += 100;
				}
			}
		}
		if (game->player[0].lives > 0)
			*player1Hit = checkCollisionPlayerBullet(*player1, *bullet, game->draw);
		if (game->twoPlayers && game->player[1].lives > 0)
			*player2Hit = checkCollisionPlayerBullet(*player2, *bullet, game->draw);
		if (*player1Hit || *player2Hit)
		{
			bullet->lifeTime = 1000.0f;
			break;
		}
	}

}

void gameCollisions(Game* game)
{
	bool player1Hit = 0;
	bool player2Hit = 0;

	PlayerCollisionBox player1 = getPlayerCollisionBox(game->player[0].rotation, game->player[0].position, 0.25f);
	PlayerCollisionBox player2 = getPlayerCollisionBox(game->player[1].rotation, game->player[1].position, 0.25f);

	bulletBulletCollisions(game, &player1Hit, &player2Hit, &player1, &player2);
	for(int i = 0; i < game->enemyCount; i++)
	{
		if ((player1Hit  && game->player[0].lives > 0)|| (player2Hit && game->player[1].lives > 0))
		{
			Player *player = &game->player[0];
			if (player2Hit)
				player = &game->player[1];
			int score = player->score;
			int lives = player->lives - 1;
			game->levelStart = false;
			*player = (Player){0};
			player->score = score;

			player->rotation = -90.0f;
			player->lives = lives;
			startLevel(game);
			initLayer(&game->layer);
			game->levelStart = false;
			break;
		}
		Enemy* enemy = &game->enemies[i];
		for(int j = 0; j < game->bulletCount; j++)
		{
			Bullet* bullet = &game->bullets[j];
			if (collisionEnemyBullet(game, enemy, bullet))
			{
				enemy->type = ET_NONE;
				bullet->lifeTime = 1000.0f;
			}
		}
		if (enemy->active)
		{
			switch(enemy->type)
			{
				case ET_FLOATING:
				{
					FloatingCollisionBox floating =
						getFloatingCollisionBox(0, enemy->position, enemy->scale);

					player1Hit = checkCollisionPlayerFloat(player1,floating);
					if (game->twoPlayers)
						player2Hit = checkCollisionPlayerFloat(player2,floating);
					if (game->draw)
					{
						drawShape(floating.rombus, ARRAY_SIZE(floating.rombus), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(floating.triangle1, ARRAY_SIZE(floating.triangle1), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(floating.triangle2, ARRAY_SIZE(floating.triangle2), (player1Hit || player2Hit) ? RED : GREEN);
					}
					if (player1Hit || player2Hit)
						enemy->hit = true;
					else
						enemy->hit = false;
				}
				break;
				case ET_MAGNETIC:
				{
					MagneticCollisionBox magnetic =
						getMagneticCollisionBox(0, enemy->position, enemy->scale);
					player1Hit = checkCollisionPlayerMagnetic(player1, magnetic);
					if (game->twoPlayers)
						player2Hit = checkCollisionPlayerMagnetic(player2, magnetic);
					if (game->draw)
					{
						drawShape(magnetic.poly, ARRAY_SIZE(magnetic.poly), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magnetic.triangle1, ARRAY_SIZE(magnetic.triangle1), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magnetic.triangle2, ARRAY_SIZE(magnetic.triangle2), (player1Hit || player2Hit) ? RED : GREEN);
					}
				}
				break;
				case ET_FIREBALL:
				{
					FireBallCollisionBox fireball =
						getFireBallCollisionBox(0, enemy->position, enemy->scale);
					player1Hit = checkCollisionPlayerFireBall(player1, fireball);
					if (game->twoPlayers)
						player2Hit = checkCollisionPlayerFireBall(player2, fireball);
					if (game->draw)
					{
						drawShape(fireball.poly, ARRAY_SIZE(fireball.poly), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(fireball.triangle1, ARRAY_SIZE(fireball.triangle1), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(fireball.triangle2, ARRAY_SIZE(fireball.triangle2), (player1Hit || player2Hit) ? RED : GREEN);
					}
				}
				break;
				case ET_MAGNETIC_FIREBALL:
				{
					MagneticFireCollisionBox magFireball =
						getMagneticFireCollisionBox(0,enemy->position, enemy->scale);
					player1Hit = checkCollisionPlayerMagneticFire(player1,
																  magFireball);
					if (game->twoPlayers)
						player2Hit = checkCollisionPlayerMagneticFire(player2,
																	  magFireball);
					if (game->draw)
					{
						drawShape(magFireball.poly, ARRAY_SIZE(magFireball.poly), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magFireball.triangle1, ARRAY_SIZE(magFireball.triangle1), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magFireball.triangle2, ARRAY_SIZE(magFireball.triangle2), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magFireball.triangle3, ARRAY_SIZE(magFireball.triangle3), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(magFireball.triangle4, ARRAY_SIZE(magFireball.triangle4), (player1Hit || player2Hit) ? RED : GREEN);
					}
				}
				break;
				case ET_MINE_LAYER:
				{
					MineLayerCollisionBox mineLayer =
						getMineLayerCollisionBox(0,enemy->position, enemy->scale);
					player1Hit = checkCollisionPlayerMineLayer(player1,
															   mineLayer);
					if (game->twoPlayers)
						player2Hit = checkCollisionPlayerMineLayer(player2,
																   mineLayer);
					if (game->draw)
					{
						drawShape(mineLayer.poly, ARRAY_SIZE(mineLayer.poly), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(mineLayer.triangle1, ARRAY_SIZE(mineLayer.triangle1), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(mineLayer.triangle2, ARRAY_SIZE(mineLayer.triangle2), (player1Hit || player2Hit) ? RED : GREEN);
						drawShape(mineLayer.triangle3, ARRAY_SIZE(mineLayer.triangle3), (player1Hit || player2Hit) ? RED : GREEN);
					}
				}
				break;
				default:
				;
			}
		}
	}
	if (game->draw)
	{
		drawShape(player1.head, ARRAY_SIZE(player1.head), (player1Hit) ? RED : GREEN);
		drawShape(player1.tail, ARRAY_SIZE(player1.tail), (player1Hit) ? RED : GREEN);
		drawPlayerGizmo(game);
		if (game->twoPlayers)
		{
			drawShape(player2.head, ARRAY_SIZE(player2.head), (player2Hit) ? RED : GREEN);
			drawShape(player2.tail, ARRAY_SIZE(player2.tail), (player2Hit) ? RED : GREEN);
		}
	}
}

static void spawnMineLayer(Game *game)
{
	Vector2d position = {10, SCREEN_HEIGHT / 2};

	initAllEnemies(game, ET_FLOATING, 7);
	for (int i = 0; i < game->enemyCount; i += 1)
	{
		game->enemies[i].position.x = GetRandomValue(-10, 10) + position.x;
		game->enemies[i].position.y = GetRandomValue(-10, 10) + position.y;
	}
	EnemyType type1 = GetRandomValue(1, 3);
	EnemyType type2 = GetRandomValue(1, 3);
	initEnemy(&game->enemies[0], position, ET_MINE_LAYER, ES_BIG);
	game->enemies[0].active = true;
	addEnemy(game, ES_BIG, type1);
	addEnemy(game, ES_BIG, type2);
	game->mineLayerSpawned = true;
}

void gameIsOver(Game* game)
{
	if (game->state == GS_PLAY && !game->twoPlayers)
	{
		if (game->player[0].lives <= 0)
			game->state = GS_GAMEOVER;
	}
	else if (game->twoPlayers)
	{
		if (game->player[0].lives <= 0 &&
			game->player[1].lives <= 0 )
			game->state = GS_GAMEOVER;
	}

	for(int i = 0; i < game->enemyCount; i++)
	{
		if (game->enemies[i].type != ET_NONE)
			return;
	}

	if (game->mineLayerSpawned)
	{
		game->level++;
		if (game->level > 5)
			game->level = 1;
		startLevel(game);
		initLayer(&game->layer);
		game->levelStart = false;
	}
	else
		spawnMineLayer(game);
}
