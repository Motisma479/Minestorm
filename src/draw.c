#include "game.h"

static void drawPauseMenu(Game *game, int frameCounter)
{
	DrawText("Resume" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
			 SCREEN_HEIGHT / 4,25, BLUE);
	DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
			 SCREEN_HEIGHT / 3,25, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("PAUSE" , SCREEN_WIDTH / 2 - MeasureText("PAUSE",25) + 67,
				 SCREEN_HEIGHT / 8,25, WHITE);
	}
	else
	{
		DrawText("SPACE",SCREEN_WIDTH/2 - MeasureText("SPACE",25) + 125,
				 SCREEN_HEIGHT / 4,25, BLUE);
		DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",25) + 125,
				 SCREEN_HEIGHT / 3,25, RED);
	}
}

static void drawMenu(Game *game, int frameCounter)
{
	DrawText("MENU" , SCREEN_WIDTH / 2 - MeasureText("MENU",25) + 67,
			 SCREEN_HEIGHT / 8,25, WHITE);
	DrawText("Single Player" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 4,25, BLUE);
	DrawText("2 Players" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 3,25, GREEN);
	DrawText("QUIT" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 2,25, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("\'F\'", SCREEN_WIDTH /2 - MeasureText("'F'",25) + 125,
				 SCREEN_HEIGHT / 4,25, BLUE);
		DrawText("\'K\'", SCREEN_WIDTH /2 - MeasureText("'F'",25) + 125,
				 SCREEN_HEIGHT / 3,25, GREEN);
		DrawText("Escape", SCREEN_WIDTH /2 - MeasureText("Escape",25) + 125,
				 SCREEN_HEIGHT / 2,25, RED);
	}
}

void drawGame(Game* game, int frameCounter)
{
	BeginDrawing();

	DrawTextureEx(game->background, (Vector2){0, 0}, 0, 1.0f, WHITE);

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
			//for(int i = 0; i < ENEMY_COUNT; i++)
			//drawEnemy(&game->enemies[i]);
			for(int i = 0; i < game->bulletCount; i++)
			{
				Bullet* bullet = &game->bullets[i];
				drawBullet(bullet, game->atlas);
			}
			drawPlayer(&game->player, 0.5f, SKYBLUE, game->atlas);
		}break;
		case GS_GAMEOVER:
		{
			DrawText("Game Over" , SCREEN_WIDTH / 2 - MeasureText("Game Over",25) + 67,
					 SCREEN_HEIGHT / 8,25, WHITE);
			DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
					 SCREEN_HEIGHT / 3,25, RED);
			if((frameCounter / 30) % 2)
			{
				DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",25) + 125,
						 SCREEN_HEIGHT / 3,25, RED);
			}
			// TODO(v.caraulan): Score
		}break;
		default:
		{

		}
	}
	DrawTextureEx(game->foreground, (Vector2){0, 0}, 0, 1.0f, WHITE);
	EndDrawing();
}
