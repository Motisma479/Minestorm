#include "game.h"
#include "draw.h"
#include "Math.h"
#include "collision.h"

int addEnemy(Game *game, EnemySize size)
{
	for (int i = 0; i < game->enemyCount;i++)
	{
		Enemy *enemy = &game->enemies[i];
		if (!enemy->active)
		{
			initEnemy(enemy, enemy->position, enemy->type, size);
			enemy->active = true;
			return (1);
		}
	}
	return (0);
}

void initLevel1(Game *game)
{
	Vector2 Random;

	game->layer = (MineLayer){0};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 1;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_FLOATING, ES_NONE);
		game->enemies[i].active = false;
	}
}

bool initGame(Game* game)
{
	game->state = GS_MENU;
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"VICTOR-MATHIEU-OSVALDO");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);

	initPlayer(&game->player[0], (Vector2){SCREEN_WIDTH / 3.0f,
				   SCREEN_HEIGHT / 2.0f});
	initPlayer(&game->player[1], (Vector2){SCREEN_WIDTH / 1.5f,
				   SCREEN_HEIGHT / 2.0f});

	initLevel1(game);

	loadData(game);
	game->ticksCount = 0;
	return true;
}

void runGameLoop(Game* game)
{
	while (!WindowShouldClose() && game->state != GS_CLOSE)
	{
		game->ticksCount = GetFrameTime();
		processInput(game);
		BeginDrawing();
		DrawTextureEx(game->background, (Vector2){0, 0}, 0, 1.0f, WHITE);
		updateGame(game);
		drawGame(game);
	}

}

int setInputFlagPressed(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyPressed(key))
	{
		*flag |= action;
		return (1);
	}
	else
		*flag &= ~action;
	return (0);
}

void setInputFlag(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyDown(key))
		*flag |= action;
	else
		*flag &= ~action;
}

void processInput(Game* game)
{
	Player *player1 = &game->player[0];
	Player *player2 = &game->player[1];
	if(IsKeyPressed(KEY_SPACE))
	{
		if (game->state == GS_PLAY)
			game->state = GS_PAUSE;
		else if (game->state == GS_PLAY2)
			game->state = GS_PAUSE2;
		else if (game->state == GS_PAUSE)
			game->state = GS_PLAY;
		else if (game->state == GS_PAUSE2)
			game->state = GS_PLAY2;
	}

	setInputFlagPressed(KEY_F, &player1->action, PA_SHOOT);
	if (!setInputFlagPressed(KEY_T, &player1->action, PA_TELEPORT))
		setInputFlagPressed(KEY_E, &player1->action, PA_TELEPORT);
	setInputFlag(KEY_D, &player1->action, PA_TURN_LEFT);
	setInputFlag(KEY_G, &player1->action, PA_TURN_RIGHT);
	setInputFlag(KEY_R, &player1->action, PA_ACCELERATION);

	if(IsKeyPressed('K') && (game->state == GS_MENU))
		game->state = GS_PLAY2;
	if (game->state == GS_PLAY2)
	{
		setInputFlagPressed(KEY_K, &player2->action, PA_SHOOT);
		if (!setInputFlagPressed(KEY_U, &player2->action, PA_TELEPORT))
			setInputFlagPressed(KEY_O, &player2->action, PA_TELEPORT);
		setInputFlag(KEY_J, &player2->action, PA_TURN_LEFT);
		setInputFlag(KEY_L, &player2->action, PA_TURN_RIGHT);
		setInputFlag(KEY_I, &player2->action, PA_ACCELERATION);
	}
	if (IsKeyPressed('C'))
	{
		if (game->drawCollisions == 0)
			game->drawCollisions = 1;
		else if (game->drawCollisions == 1)
			game->drawCollisions = 2;
		else
			game->drawCollisions = 0;
	}

	if(IsKeyPressed(KEY_ESCAPE))
	{
		if (game->state == GS_MENU)
			game->state = GS_CLOSE;
		if (game->state == GS_PAUSE  ||
			game->state == GS_PAUSE2 ||
			game->state == GS_GAMEOVER ||
			game->state == GS_GAMEOVER2)
		{
			game->state = GS_MENU;
			*player1 = (Player){0};
			*player2 = (Player){0};
			initPlayer(player1, (Vector2){SCREEN_WIDTH / 3.0f,
						   SCREEN_HEIGHT / 2.0f});
			initPlayer(player2, (Vector2){SCREEN_WIDTH / 1.5f,
						   SCREEN_HEIGHT / 2.0f});
			initLevel1(game);
			game->levelStart = false;
		}
	}
}

void updateGame(Game* game)
{
	switch(game->state)
	{
		case GS_MENU:
		{
			if (game->player[1].action & PA_SHOOT)
			{
				game->state = GS_PLAY2;
				game->player[1].action &= ~(PA_SHOOT);
			}
			else if (game->player[0].action & PA_SHOOT)
				game->state = GS_PLAY;
			game->player[0].action &= ~(PA_SHOOT);
			game->framesCounter++;
		}break;
		case GS_PLAY:
		case GS_PLAY2:
		{
			if (game->levelStart == false)
			{
				if (updateLayer(&game->layer, game->ticksCount))
				{
					game->levelStart = true;
					addEnemy(game, ES_BIG);
					addEnemy(game, ES_BIG);
				}
			}
			if (game->levelStart)
			{
				updatePlayer(&game->player[0], game->ticksCount);
				if (game->player[0].action & PA_SHOOT)
				{
					gameAddBullet(&game->player[0]);
					game->player[0].action &= ~PA_SHOOT;
				}
				for(int i = 0; i < game->player[0].bulletCount; i++)
				{
					Bullet* bullet = &game->player[0].bullets[i];
					updateBullet(bullet,game->ticksCount);
				}
				if (game->state == GS_PLAY2)
				{
					updatePlayer(&game->player[1], game->ticksCount);
					if (game->player[1].action & PA_SHOOT)
						gameAddBullet(&game->player[1]);
					for(int i = 0; i < game->player[1].bulletCount; i++)
					{
						Bullet* bullet = &game->player[1].bullets[i];
						updateBullet(bullet,game->ticksCount);
					}
				}

				for(int i = 0; i < game->enemyCount; i++)
					updateEnemy(&game->enemies[i], game->ticksCount);
				gameCollisions(game, &game->player[0]);
				if (game->state == GS_PLAY2)
					gameCollisions(game, &game->player[1]);
				gameRemoveBullet(&game->player[0]);
				gameRemoveBullet(&game->player[1]);
				gameIsOver(game);
			}
		} break;
		default:
		{
			game->framesCounter++;
		}
	}
}


void gameAddBullet(Player *player)
{
	Vector2 *position = &player->position;
	float   rotation = player->rotation;
	if(player->bulletCount == BULLET_CAPACITY)
		return;

	Bullet bullet = {0};

	initBullet(&bullet, *position, rotation);

	player->bullets[player->bulletCount] = bullet;
	player->bulletCount += 1;
}

void gameRemoveBullet(Player *player)
{

	for(int i = 0; i < player->bulletCount; i++)
	{
		Bullet* bullet = &player->bullets[i];

		if (lengthVector2d((Vector2d){bullet->addPosition.x, bullet->addPosition.y}) > SCREEN_HEIGHT / 2)
		{
			player->bullets[i] = player->bullets[player->bulletCount - 1];
			player->bulletCount -= 1;
		}
	}
}

int gameEnemyAliveCount(Game* game)
{
	int count = 0;
	for(int i = 0; i < game->enemyCount; i++)
	{
		//if(game->enemies[i].life > 0)
		//count++;
	}
	return count;
}
void loadData(Game* game)
{
	game->atlas = LoadTexture("assets/mines.png");
	game->background = LoadTexture("assets/background.png");
	game->foreground = LoadTexture("assets/foreground.png");
}

void unloadData(Game* game)
{
	UnloadTexture(game->atlas);
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
}

//TODO : Collisions

int collisionEnemyBullet(Game *game, Player *player, Enemy *enemy, Bullet *bullet)
{
	Rectangle enemyRec = {enemy->position.x, enemy->position.y, 25, 25};
	Rectangle bulletRec = {bullet->position.x, bullet->position.y, 25 / 4, 25 / 4};
	if (enemy->active && enemy->type != ET_NONE)
	{

		// TODO(v.caraulan): Replace with our functions
		if (CheckCollisionRecs(bulletRec, enemyRec))
		{
			switch(enemy->size)
			{
				case ES_SMALL:
				{
					player->score += 200;
				}break;
				case ES_MEDIUM:
				{
					addEnemy(game, ES_SMALL);
					addEnemy(game, ES_SMALL);
					player->score += 135;
				}break;
				case ES_BIG:
				{
					addEnemy(game, ES_MEDIUM);
					addEnemy(game, ES_MEDIUM);
					player->score += 100;
				}break;
				default:
				break;
			}
			enemy->type = ET_NONE;
			bullet->position.x = -1;
			bullet->position.y = -1;
			return (1);
		}
	}
	return (0);
}

void gameCollisions(Game* game, Player *player)
{
	for(int j = 0; j < game->enemyCount; j++)
	{
		Enemy* enemy = &game->enemies[j];
		for(int i = 0; i < player->bulletCount; i++)
		{
			Bullet* bullet = &player->bullets[i];
			if (collisionEnemyBullet(game, player, enemy, bullet))
				break;
		}
		if (enemy->active)
		{
			Vector2d enemyPosition = (Vector2d){enemy->position.x, enemy->position.y};
			bool intersect = 0;
			switch(enemy->type)
			{
				case ET_FLOATING:
				{
					FloatingCollisionBox floating =
						getFloatingCollisionBox(0, enemyPosition, enemy->scale);
					intersect = checkCollisionPlayerFloat(*player,floating, game->drawCollisions);
				}
				break;
				case ET_MAGNETIC:
				{
					MagneticCollisionBox magnetic =
						getMagneticCollisionBox(0, enemyPosition, enemy->scale);

					intersect = checkCollisionPlayerMagnetic(*player, magnetic, game->drawCollisions);
				}
				break;
				case ET_FIREBALL:
				{
					FireBallCollisionBox fireball =
						getFireBallCollisionBox(0, enemyPosition, enemy->scale);
					intersect = checkCollisionPlayerFireBall(*player, fireball, game->drawCollisions);
				}
				break;
				case ET_MAGNETIC_FIREBALL:
				{
					MagneticFireBallCollisionBox fireball =
						getMagneticFireballCollisionBox(0,enemyPosition, enemy->scale);
					intersect = checkCollisionPlayerMagneticFireBall(*player,
																	 fireball,
																	 game->drawCollisions);
				}
				break;
				default:
				;
			}
			if (intersect)
			{
				int score = player->score;
				int lives = player->lives - 1;
				game->levelStart = false;
				*player = (Player){0};
				player->score = score;
				player->position.x = SCREEN_WIDTH / 3.0f;
				player->position.y = SCREEN_HEIGHT / 2.0f;
				player->rotation = -90.0f;
				player->lives = lives;
				initLevel1(game);
			}
		}
	}
}

void gameIsOver(Game* game)
{
	if (game->state == GS_PLAY)
	{
		if (game->player[0].lives <= 0)
			game->state = GS_GAMEOVER;
	}
	else if (game->state == GS_PLAY2)
	{
		if (game->player[0].lives <= 0 &&
			game->player[1].lives <= 0 )
			game->state = GS_GAMEOVER2;
	}



	for(int i = 0; i < game->enemyCount; i++)
	{
		if (game->enemies[i].type != ET_NONE)
			return;
	}
	game->level++;
	game->levelStart = false;
	switch(game->level)
	{
		case 2: initLevel1(game);break;
		case 3: initLevel1(game);break;
		case 4: initLevel1(game);break;
		case 5: initLevel1(game);break;
	}
}

void Shutdown(Game* game)
{
	game->state = GS_CLOSE;
	unloadData(game);
	CloseWindow();
}