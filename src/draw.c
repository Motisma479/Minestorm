#include "game.h"

static void drawLives(Game *game, Player *player, Vector2 offset, Color color)
{
	float scale = 0.1f;
	if (player->lives > 0)
		drawPlayer(player, scale, color, game->atlas);
	player->position = (Vector2){80+offset.x, 30+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, game->atlas);
	player->position = (Vector2){100+offset.x, 30+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, game->atlas);
}

static void drawLives2(Game *game, Player *player, Vector2 offset, Color color)
{
	float scale = 0.1f;
	player->rotation = -90.0f;
	player->position = (Vector2){530-offset.x, 30+offset.y};
	if (player->lives > 0)
		drawPlayer(player, scale, color, game->atlas);
	player->position = (Vector2){550-offset.x, 30+offset.y};
	if (player->lives > 1)
		drawPlayer(player, scale, color, game->atlas);
	player->position = (Vector2){570-offset.x, 30+offset.y};
	if (player->lives > 2)
		drawPlayer(player, scale, color, game->atlas);
}

static void drawScoreBoard(Game *game, Vector2 offset)
{
	Player player = game->player[0];
	player.position = (Vector2){60 + offset.x, 30 + offset.y};
	player.rotation = -90.0f;

	DrawRectangle(40+offset.x, 0+offset.y, 240, 40, SKYBLUE);
	DrawText("Player ONE", 45+offset.x, 0+offset.y, 20, BLUE);

	drawLives(game, &player, offset, BLUE);

	DrawText(TextFormat("%d", game->player[0].score), 240+offset.x,
			 0+offset.y, 20, BLUE);

	if (game->state == GS_PLAY2  || game->state == GS_PAUSE2 ||
		game->state == GS_GAMEOVER2)
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
	BeginDrawing();

	DrawTextureEx(game->background, (Vector2){0, 0}, 0, 1.0f, WHITE);
	switch(game->state)
	{
		case GS_MENU:
		{
			drawMenu(game);
		}break;
		case GS_PAUSE:
		case GS_PAUSE2:
		{
			drawPauseMenu(game);
		}break;
		case GS_PLAY:
		case GS_PLAY2:
		{
			for(int i = 0; i < game->enemyCount; i++)
				drawEnemy(&game->enemies[i], game->atlas);
			for(int i = 0; i < game->player[0].bulletCount; i++)
			{
				Bullet* bullet = &game->player[0].bullets[i];
				drawBullet(bullet, game->atlas, SKYBLUE);
			}

			drawLayer(&game->layer, game->atlas);
			drawPlayer(&game->player[0], 0.25f, SKYBLUE, game->atlas);
			if (game->state == GS_PLAY2)
			{
				for(int i = 0; i < game->player[1].bulletCount; i++)
				{
					Bullet* bullet = &game->player[1].bullets[i];
					drawBullet(bullet, game->atlas, GREEN);
				}
				drawPlayer(&game->player[1], 0.25f, GREEN, game->atlas);
			}
		}break;
		default:
		{

		}
	}
	DrawTextureEx(game->foreground, (Vector2){0, 0}, 0, 1.0f, WHITE);
	drawScoreBoard(game, (Vector2){0, 0});
	if (game->state == GS_GAMEOVER  || game->state == GS_GAMEOVER2)
	{
		drawScoreBoard(game, (Vector2){30, 400});
		drawGameOver(game);
	}
	EndDrawing();
}
