#include "game.h"
#include "draw.h"
#include "player.h"

static void drawLives(Game *game, Player *player, Vector2d offset, Color color)
{
	float scale = 0.1f;
	if (player->lives > 0)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){220+offset.x, 12+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){240+offset.x, 12+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, &game->atlas);
}

static void drawLives2(Game *game, Player *player, Vector2d offset, Color color)
{
	float scale = 0.1f;
	player->rotation = -90.0f;
	player->position = (Vector2d){SCREEN_WIDTH-53-offset.x, 12+offset.y};
	if (player->lives > 0)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){SCREEN_WIDTH-73-offset.x, 12+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){SCREEN_WIDTH-93-offset.x, 12+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, &game->atlas);
}

static void drawScoreBoard(Game *game, Vector2d offset)
{
	Player player = game->player[0];
	player.position = (Vector2d){200 + offset.x, 12 + offset.y};
	player.rotation = -90.0f;

	DrawText("P1", 45+offset.x, 0+offset.y, 15, BLUE);

	drawLives(game, &player, offset, BLUE);

	DrawText(TextFormat("%d", game->player[0].score), 70+offset.x,
			 0+offset.y, 15, BLUE);

	if (game->twoPlayers)
	{
		DrawText("P2", 420 + offset.x, 0+offset.y, 15, LIME);

		player = game->player[1];
		drawLives2(game, &player, offset, LIME);
		DrawText(TextFormat("%d", game->player[1].score), 445 + offset.x,
				 0 + offset.y, 15, LIME);
	}
	if ((game->framesCounter / 30) % 100)
		DrawText("||", 490, 750, 25, YELLOW);
	DrawText("  SPACE", 490, 750, 25, YELLOW);
}

static void drawPauseMenu(Game *game)
{
	DrawText("FIRE", 80, 80, 20, BLUE);
	DrawText("ACCELERATE", 80, 100, 20, BLUE);
	DrawText("TURN LEFT", 80, 120, 20, BLUE);
	DrawText("TURN RIGHT", 80, 140, 20, BLUE);
	DrawText("TELEPORT", 80, 160, 20, BLUE);

	DrawText("FIRE", 385, 80, 20, GREEN);
	DrawText("ACCELERATE", 385, 100, 20, GREEN);
	DrawText("TURN LEFT", 385, 120, 20, GREEN);
	DrawText("TURN RIGHT", 385, 140, 20, GREEN);
	DrawText("TELEPORT", 385, 160, 20, GREEN);

	DrawText("F",  225, 80, 20, BLUE);
	DrawText("R",  225, 100, 20, BLUE);
	DrawText("D",  225, 120, 20, BLUE);
	DrawText("G",  225, 140, 20, BLUE);
	DrawText("E",  225, 160, 20, BLUE);
	DrawText("T",  245, 160, 20, BLUE);
	DrawText("K",  530, 80, 20, GREEN);
	DrawText("I",  530, 100, 20, GREEN);
	DrawText("J",  530, 120, 20, GREEN);
	DrawText("L",  530, 140, 20, GREEN);
	DrawText("U",  530, 160, 20, GREEN);
	DrawText("O",  550, 160, 20, GREEN);

	DrawText("Resume" , 126, 200,25, BLUE);
	DrawText("Main Menu" , 126, 266,25, RED);
	if((game->framesCounter / 30) % 3)
		DrawText("PAUSE" , 285, 100, 25, WHITE);
	else
	{
		DrawText("SPACE", 362, 200,25, BLUE);
		DrawText("Esc", 401, 266, 25, RED);
	}
}

static void drawGameOver(Game *game)
{
	DrawText("Game Over" , 259, 100,25, WHITE);

	DrawText("Main Menu" , 126, 266,25, RED);

	DrawRectangleRounded((Rectangle){150, 490, 280, 50}, 0.5f, 1, WHITE);
	DrawText(TextFormat("HIGH SCORE: %d",game->highScore) , 159, 500,25, BLACK);
	if((game->framesCounter / 30) % 3)
	{
		DrawText("Esc", 401, 266,25, RED);
	}
}

static void drawMenu(Game *game)
{
	DrawText("FIRE", 80, 80, 20, BLUE);
	DrawText("ACCELERATE", 80, 100, 20, BLUE);
	DrawText("TURN LEFT", 80, 120, 20, BLUE);
	DrawText("TURN RIGHT", 80, 140, 20, BLUE);
	DrawText("TELEPORT", 80, 160, 20, BLUE);

	DrawText("FIRE", 385, 80, 20, GREEN);
	DrawText("ACCELERATE", 385, 100, 20, GREEN);
	DrawText("TURN LEFT", 385, 120, 20, GREEN);
	DrawText("TURN RIGHT", 385, 140, 20, GREEN);
	DrawText("TELEPORT", 385, 160, 20, GREEN);

	DrawText("F",  225, 80, 20, BLUE);
	DrawText("R",  225, 100, 20, BLUE);
	DrawText("D",  225, 120, 20, BLUE);
	DrawText("G",  225, 140, 20, BLUE);
	DrawText("E",  225, 160, 20, BLUE);
	DrawText("T",  245, 160, 20, BLUE);
	DrawText("K",  530, 80, 20, GREEN);
	DrawText("I",  530, 100, 20, GREEN);
	DrawText("J",  530, 120, 20, GREEN);
	DrawText("L",  530, 140, 20, GREEN);
	DrawText("U",  530, 160, 20, GREEN);
	DrawText("O",  550, 160, 20, GREEN);

	DrawText("MENU"          , 285, 100, 25, WHITE);
	DrawText("Single Player" , 159, 300, 25, BLUE);
	DrawText("2 Players"     , 159, 366, 25, GREEN);
	DrawText("QUIT"          , 159, 550, 25, RED);

	if((game->framesCounter / 30) % 3)
	{
		DrawText("\'F\'" , 416, 300,25, BLUE);
		DrawText("\'K\'" , 416, 366,25, GREEN);
		DrawText("Escape", 358, 550,25, RED);
	}
}

void drawGame(Game* game)
{
	switch(game->state)
	{
		case GS_MENU: drawMenu(game);break;
		case GS_PAUSE: drawPauseMenu(game);break;
		case GS_PLAY:
		{
			if (game->draw != DS_COLLISIONS)
			{
				if (game->levelStart)
				{
					for(int i = 0; i < game->enemyCount; i++)
						drawEnemy(&game->enemies[i], game->atlas);
					for(int i = 0; i < game->bulletCount; i++)
					{
						Bullet* bullet = &game->bullets[i];
						if (bullet->source == BS_PLAYER1)
							drawBullet(bullet, &game->atlas, SKYBLUE);
						else if (bullet->source == BS_PLAYER2)
							drawBullet(bullet, &game->atlas, GREEN);
						else if (bullet->source == BS_ENEMY)
							drawBullet(bullet, &game->atlas, RED);
					}
					drawPlayer(&game->player[0], 0.25f, SKYBLUE, &game->atlas);
					if (game->twoPlayers)
						drawPlayer(&game->player[1], 0.25f, GREEN, &game->atlas);
				}
				drawLayer(&game->layer, &game->atlas);
			}
		}break;
		default:;
	}
	DrawTexturePro(game->foreground,
				   (Rectangle){38, 40, game->foreground.width - 77,
					   game->foreground.height - 81} ,
				   (Rectangle){0, 0, game->foreground.width,
					   game->foreground.height},
				   (Vector2){0, 0}, 0, WHITE);
	drawScoreBoard(game, (Vector2d){0, 0});
	if (game->state == GS_GAMEOVER)
	{
		drawScoreBoard(game, (Vector2d){30, 400});
		drawGameOver(game);
	}
	EndDrawing();
}

void drawPlayerGizmo(Game* game)
{
	int count = 1;
	if (game->twoPlayers)
		count = 2;
	for(int i = 0; i < count; i++)
	{
		float endX1 = game->player[i].position.x +
		getDirection(game->player[i].rotation).x*30;
		float endY1 = game->player[i].position.y +
		getDirection(game->player[i].rotation).y*30;
		float endX2 = game->player[i].position.x +
		getDirection(game->player[i].rotation + 90.0f).x*30 ;
		float endY2 = game->player[i].position.y +
		getDirection(game->player[i].rotation + 90.0f).y*30;

		DrawLine(game->player[i].position.x,game->player[i].position.y,endX1,endY1,BLUE);
		DrawLine(game->player[i].position.x,game->player[i].position.y,endX2,endY2,RED);
	}
}

void drawEnemyGizmo(Game* game)
{
	for(int i = 0; i < game->enemyCount ; i++)
	{
		if(game->enemies[i].type != ET_NONE && game->enemies[i].active)
		{
			float endX1 = game->enemies[i].position.x + getDirection(game->enemies[i].rotation).x*35;
			float endY1 = game->enemies[i].position.y + getDirection(game->enemies[i].rotation).y*35;

			float endX2 = game->enemies[i].position.x + getDirection(game->enemies[i].rotation + 90.0f).x*35;
			float endY2 = game->enemies[i].position.y + getDirection(game->enemies[i].rotation + 90.0f).y*35;

			DrawLine(game->enemies[i].position.x  ,game->enemies[i].position.y,endX1,endY1,RED);
			DrawLine(game->enemies[i].position.x  ,game->enemies[i].position.y,endX2,endY2,BLUE);
		}

	}
}
