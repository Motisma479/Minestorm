#include "game.h"

static void drawPauseMenu(Game *game, int frameCounter)
{
	DrawText("Resume" , SCREEN_WIDTH / 3 - MeasureText("Resume",50),
			 SCREEN_HEIGHT / 4,50, BLUE);
	DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",50),
			 SCREEN_HEIGHT / 3,50, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("PAUSE" , SCREEN_WIDTH / 2 - MeasureText("PAUSE",50) + 67,
				 SCREEN_HEIGHT / 8,50, WHITE);
	}
	else
	{
		DrawText("SPACE",SCREEN_WIDTH/2 - MeasureText("SPACE",50) + 150,
				 SCREEN_HEIGHT / 4,50, BLUE);
		DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",50) + 150,
				 SCREEN_HEIGHT / 3,50, RED);
	}
}

static void drawMenu(Game *game, int frameCounter)
{
	DrawText("MENU" , SCREEN_WIDTH / 2 - MeasureText("MENU",50) + 67,
			 SCREEN_HEIGHT / 8,50, WHITE);
	DrawText("Single Player" , SCREEN_WIDTH / 2 - MeasureText("Single Player",50),
			 SCREEN_HEIGHT / 4,50, BLUE);
	DrawText("2 Players" , SCREEN_WIDTH / 2 - MeasureText("Single Player",50),
			 SCREEN_HEIGHT / 3,50, GREEN);
	DrawText("QUIT" , SCREEN_WIDTH / 2 - MeasureText("Single Player",50),
			 SCREEN_HEIGHT / 2,50, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("\'F\'", SCREEN_WIDTH /2 - MeasureText("'F'",50) + 150,
				 SCREEN_HEIGHT / 4,50, BLUE);
		DrawText("\'K\'", SCREEN_WIDTH /2 - MeasureText("'F'",50) + 150,
				 SCREEN_HEIGHT / 3,50, GREEN);
		DrawText("Escape", SCREEN_WIDTH /2 - MeasureText("Escape",50) + 150,
				 SCREEN_HEIGHT / 2,50, RED);
	}
}

void drawGame(Game* game, int frameCounter)
{
	BeginDrawing();

	DrawTextureEx(game->background, (Vector2){0, 0}, 0, 1.5f, WHITE);

	switch(game->state)
	{
		case GS_MENU:
		{
			drawMenu(game, frameCounter);
		}break;
		case GS_PAUSE:
		{
			drawPauseMenu(game, frameCounter);
		}break;
		case GS_PLAY:
		{
			for(int i = 0; i < ENEMY_COUNT; i++)
				drawEnemy(&game->enemies[i]);
			for(int i = 0; i < game->bulletCount; i++)
			{
				Bullet* bullet = &game->bullets[i];
				drawBullet(bullet, &game->atlas);
			}
			drawPlayer(&game->player, 0.5f, GREEN);
		}break;
		case GS_GAMEOVER:
		{
			DrawText("Game Over" , SCREEN_WIDTH / 2 - MeasureText("Game Over",50) + 67,
					 SCREEN_HEIGHT / 8,50, WHITE);
			DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",50),
					 SCREEN_HEIGHT / 3,50, RED);
			if((frameCounter / 30) % 2)
			{
				DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",50) + 150,
						 SCREEN_HEIGHT / 3,50, RED);
			}
			// TODO(v.caraulan): Score
		}break;
		default:
		{

		}
	}
	DrawTextureEx(game->foreground, (Vector2){0, 0}, 0, 1.5f, WHITE);
	EndDrawing();
}
