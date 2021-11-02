#include "game.h"
#include "draw.h"
#include "player.h"

static void drawLives(Game *game, Player *player, Vector2d offset, Color color)
{
	float scale = 0.1f;
	if (player->lives > 0)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){80+offset.x, 30+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){100+offset.x, 30+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, &game->atlas);
}

static void drawLives2(Game *game, Player *player, Vector2d offset, Color color)
{
	float scale = 0.1f;
	player->rotation = -90.0f;
	player->position = (Vector2d){530-offset.x, 30+offset.y};
	if (player->lives > 0)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){550-offset.x, 30+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, &game->atlas);
	player->position = (Vector2d){570-offset.x, 30+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, &game->atlas);
}

static void drawScoreBoard(Game *game, Vector2d offset)
{
	Player player = game->player[0];
	player.position = (Vector2d){60 + offset.x, 30 + offset.y};
	player.rotation = -90.0f;

	DrawRectangle(40+offset.x, 0+offset.y, 250, 40, SKYBLUE);
	DrawText("Player ONE", 45+offset.x, 0+offset.y, 20, BLUE);

	drawLives(game, &player, offset, BLUE);

	DrawText(TextFormat("%d", game->player[0].score), 240+offset.x,
			 0+offset.y, 20, BLUE);

	if (game->twoPlayers)
	{
		DrawRectangle(364-offset.x, 0+offset.y, 230, 40, GREEN);
		DrawText("Player TWO", 470-offset.x, 0+offset.y, 20, LIME);

		player = game->player[1];
		drawLives2(game, &player, offset, LIME);
		DrawText(TextFormat("%d", game->player[1].score), 370 - offset.x,
				 0 + offset.y, 20, LIME);
	}
}

static void drawPauseMenu(Game *game)
{
	DrawText("Resume" , 126, 200,25, BLUE);
	DrawText("Main Menu" , 126, 266,25, RED);
	if((game->framesCounter / 30) % 2)
		DrawText("PAUSE" , 304, 100, 25, WHITE);
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
	if((game->framesCounter / 30) % 2)
	{
		DrawText("Esc", 401, 266,25, RED);
	}
}

static void drawMenu(Game *game)
{
	DrawText("MENU"          , 319, 100, 25, WHITE);
	DrawText("Single Player" , 159, 200, 25, BLUE);
	DrawText("2 Players"     , 159, 266, 25, GREEN);
	DrawText("QUIT"          , 159, 400, 25, RED);
	if((game->framesCounter / 30) % 2)
	{
		DrawText("\'F\'" , 416, 200,25, BLUE);
		DrawText("\'K\'" , 416, 266,25, GREEN);
		DrawText("Escape", 358, 400,25, RED);
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
	DrawTextureEx(game->foreground, (Vector2){0, 0}, 0, 1.0f, WHITE);
	drawScoreBoard(game, (Vector2d){0, 0});
	if (game->state == GS_GAMEOVER)
	{
		drawScoreBoard(game, (Vector2d){30, 400});
		drawGameOver(game);
	}
	DrawFPS(0, 0);
	EndDrawing();
}
