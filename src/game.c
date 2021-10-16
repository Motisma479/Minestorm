#include "game.h"
#include <stdlib.h>

static int framesCounter = 0;
bool initGame(Game* game)
{
	game->gameIsRunning = true;
    game->gamePaused = false;
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"VICTOR-MATHIEU-OSVALDO");
    SetTargetFPS(60);

    //Init Player
    initPlayer(&game->player);


	//----------------------------
	// TODO(v.caraulan): This is not permanent,
	// Have to free this at the end if I decide this is how we're going to do this
	unsigned char *mem = malloc((sizeof(Enemy) * ENEMY_COUNT) +
								(sizeof(Bullet) * BULLET_CAPACITY) * 2);
	game->enemies = (Enemy *)mem;
	game->bullets = (Bullet *)(mem + (sizeof(Enemy) * ENEMY_COUNT));
	//----------------------------

    /////inti ememies
    for(int i = 0; i < ENEMY_COUNT; i++)
    {
		initEnemy(&game->atlas, &game->enemies[i]);
    }

    //load data
    loadData(game);

    if(!game->gameIsRunning)
    {

        return false;
    }

    game->ticksCount = 0;

    return true;
}
void runLoop(Game* game)
{
    while (!WindowShouldClose() && game->gameIsRunning)
    {
        processInput(game);
        updateGame(game);
        drawGame(game);
    }

}
void processInput(Game* game)
{
    if(IsKeyPressed(KEY_P))
        game->gamePaused = !game->gamePaused;

    //player inputs
    inputPlayer(&game->player);

    //add bullet to the game
    if(IsKeyPressed(KEY_SPACE))
        gameAddBullet(game,game->player.position);

}
void updateGame(Game* game)
{
    game->ticksCount = GetFrameTime();
    if(!game->gamePaused)
    {
        //update all objects in game
        updatePlayer(&game->player,game->ticksCount);

        //update enemies
        for(int i = 0; i < ENEMY_COUNT; i++)
        {
			updateEnemy(&game->enemies[i],game->ticksCount);
        }

        //update bullets
        for(int i = 0; i < game->bulletCount; i++)
        {
			Bullet* bullet = &game->bullets[i];
			updateBullet(bullet,game->ticksCount);
        }
        gameRemoveBullet(game);

        //show game's stats
        gameStats(game);

        //check if there no more enemies
        gameIsOver(game);

    }
    else
    {
        //TODO
        framesCounter++;

    }
}

void gameStats(Game* game)
{
    DrawText(TextFormat("Enemy count: %d",gameEnemyAliveCount(game)),10,10,20,PURPLE);
    DrawText(TextFormat("Bullet count: %d",game->bulletCount),10,50,20,PURPLE);
}

void drawGame(Game* game)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
	DrawTexture(game->background, 0,0,RAYWHITE);
    if(!game->gamePaused)
    {

        //draw enemies
        for(int i = 0; i < ENEMY_COUNT; i++)
        {
			drawEnemy(&game->enemies[i]);
        }

        //draw bullets
        for(int i = 0; i < game->bulletCount; i++)
        {
			Bullet* bullet = &game->bullets[i];
			drawBullet(bullet, &game->atlas);
        }

        //draw Player
		drawPlayer(&game->player, 0.5f, GREEN);
    }
	DrawTexture(game->foreground, 0,0,RAYWHITE);
    if(game->gamePaused && (framesCounter/30)%2)
    {
        DrawText("GAME PAUSED",SCREEN_WIDTH/2 - MeasureText("GAME PAUSED",50) + 150,
				 SCREEN_HEIGHT / 2,50,PURPLE);
    }


    EndDrawing();
}

void gameAddBullet(Game* game, Vector2 position)
{
    if(game->bulletCount == BULLET_CAPACITY)
    {
        return;
    }

    Bullet bullet = {0};

    //inti bullet
    initBullet(&bullet,position, game->player.rotation);

    game->bullets[game->bulletCount] = bullet;
    game->bulletCount += 1;
}

void gameRemoveBullet(Game* game)
{
    //remove bullets
    for(int i = 0; i < game->bulletCount; i++)
    {
        Bullet* bullet = &game->bullets[i];

        if(bullet->position.x < 0.0f || bullet->position.x > (float) SCREEN_WIDTH
		   || bullet->position.y < 0.0f || bullet->position.y > (float)SCREEN_HEIGHT)
        {
            game->bullets[i] = game->bullets[game->bulletCount - 1];
            game->bulletCount -= 1;
		}
    }
}

int gameEnemyAliveCount(Game* game)
{
    int count = 0;
    for(int i = 0; i < ENEMY_COUNT; i++)
    {
        if(game->enemies[i].life > 0)
            count++;
    }

    return count;
}
void loadData(Game* game)
{
    game->atlas = LoadTexture("assets/mines.png");
	game->background = LoadTexture("assets/background.png");
	game->foreground = LoadTexture("assets/foreground.png");
	game->player.texture = &game->atlas;
}

void unloadData(Game* game)
{
	UnloadTexture(game->atlas);
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
}

//TODO : Collisions
void gameCollisions(Game* game)
{
    for(int i = 0; i < game->bulletCount; i++)
    {
        //Bullet* bullet = &game->bullets[i];
        for(int j = 0; j < ENEMY_COUNT; j++)
        {
            //Enemy* enemy = &game->enemies[j];

        }
    }
}

void gameIsOver(Game* game)
{
    for(int i = 0; i < ENEMY_COUNT; i++)
    {
        if(game->enemies[i].life > 0)
            return;
    }

    game->gameIsRunning = false;
}

void Shutdown(Game* game)
{
    game->gameIsRunning = false;
    if(!game->gameIsRunning)
    {
        unloadData(game);
        CloseWindow();
    }  
}