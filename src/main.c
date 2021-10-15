#include <raylib.h>
#include "minestorm.h"


#if 0
void DrawEnemy4(Game *game, Vector2 Position, float rotation, float scale, Color color)
{
	Vector2 Size = {30 * scale, 28 * scale};
	Position.x += game->playArea.x;
	Position.y += game->playArea.y;
	DrawTexturePro(game->atlas, (Rectangle){880, 110, 40, 40},
				   (Rectangle){Position.x, Position.y, Size.x, Size.y},
				   (Vector2){0, 0}, rotation, color);
}
#endif

// TODO(v.caraulan): These are not enemies, I should rename the functions

void DrawEnemy3(Game *game, Vector2 Position, float rotation, float scale, Color color)
{
	Vector2 Size = {30 * scale, 28 * scale};
	Position.x += game->playArea.x;
	Position.y += game->playArea.y;
	DrawTexturePro(game->atlas, (Rectangle){880, 110, 40, 40},
				   (Rectangle){Position.x, Position.y, Size.x, Size.y},
				   (Vector2){0, 0}, rotation, color);
}

void DrawEnemy2(Game *game, Vector2 Position, float rotation, float scale, Color color)
{
	Vector2 Size = {270 * scale, 90 * scale};
	Position.x += game->playArea.x;
	Position.y += game->playArea.y;
	DrawTexturePro(game->atlas, (Rectangle){510, 90, 270, 90},
				   (Rectangle){Position.x, Position.y, Size.x, Size.y},
				   (Vector2){0, 0}, rotation, color);
}

void DrawEnemy1(Game *game, Vector2 Position, float rotation, float scale, Color color)
{
	Vector2 Size = {75 * scale, 75 * scale};
	Position.x += game->playArea.x;
	Position.y += game->playArea.y;
	DrawTexturePro(game->atlas, (Rectangle){345, 90, 75, 75},
				   (Rectangle){Position.x, Position.y, Size.x, Size.y},
				   (Vector2){0, 0}, rotation, color);
}

void DrawPlayer(Game *game, Vector2 Position, float rotation, float scale, Color color)
{
	Vector2 Size = {180 * scale, 208 * scale};
	Position.x += game->playArea.x;
	Position.y += game->playArea.y;
	DrawTexturePro(game->atlas, (Rectangle){75, 45, 180, 208},
				   (Rectangle){Position.x, Position.y, Size.x, Size.y},
				   (Vector2){0, 0}, rotation, color);
}

int main(void)
{
	Game game = {0};

	game.playArea.x = 60;
	game.playArea.y = 60;
	game.playArea.width =  520;
	game.playArea.height = 650;
	game.player1 = (Vector2){0, 0};
	game.player2 = (Vector2){0, 100};

    const int screenWidth  = 640;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Main game loop
	game.foreground = LoadTexture("assets/minestorm_foreground.png");
	game.background = LoadTexture("assets/minestorm_background.png");
	game.atlas = LoadTexture("assets/minestorm_sprite_atlas_mine_storm.png");
	while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		DrawTexture(game.background, 0,0,RAYWHITE);
		//DrawRectangle(60, 60, 520, 650, GREEN);
		DrawTexture(game.foreground, 0,0,RAYWHITE);
		DrawPlayer(&game, game.player1, 0.0f, 0.5f, BLUE);
		//DrawPlayer(&game, game.player2, 0.0f, 0.5f, GREEN);
		DrawEnemy3(&game, game.player2, 0.0f, 1, GREEN);
		EndDrawing();
    }

    CloseWindow();

    return 0;
}