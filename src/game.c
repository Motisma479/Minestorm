#include "game.h"
//#include "testCollision.h"
#include "Math.h"

static int frameCount = 0;

bool initGame(Game* game)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "[--MATHIEU-VICTOR-OSVALDO--GP1--MINESTORM PROJECT--ISART DIGITAL--]");
	SetTargetFPS(60);

	game->gamePaused = false;
	game->gameIsRunning = true;
	game->bulletCount = 0;
	
	//loadGameData(game);

	/*initPlayer(&game->player);
	game->player.active = true;*/

	    //inti ememies
    /*for(int i = 0; i < ENEMY_COUNT; i++)
    {
        initFloatingMine(&game->enemies[i]);
    }*/

	if(!game->gameIsRunning)
		return false;

	return true;
}
void processInput(Game* game)
{
	/*if (IsKeyPressed(KEY_F) && game->gameIsRunning && !game->layer.active)
	{
		initLayer(&game->layer);
		game->layer.active = true;
	}*/

	if (IsKeyDown(KEY_ESCAPE) && game->gameIsRunning)
	{
		game->gameIsRunning = false;
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		game->gamePaused = !game->gamePaused;
	}

	//add bullet to the game
    /*if(IsKeyPressed(KEY_F))
	{
		gameAddBullet(game,game->player.position);
	}*/
        

 	//inputsPlayer(&game->player);
}
void updateGame(Game* game)
{
	//float deltaTime = GetFrameTime();
	//if (game->layer.layerEnd && !game->player.active)
	//{
		//initPlayer(&game->player);
		//game->player.active = true;
	//}
	if (!game->gamePaused)
	{
		//TODO : updating all game objects
		//update enemies
        /*for(int i = 0; i < ENEMY_COUNT; i++)
        {
            updateFloatingMine(&game->enemies[i],deltaTime);
        }

		updateLayer(&game->layer,deltaTime);
		updatePlayer(&game->player, deltaTime);
		*/
		//update bullets
        /*for(int i = 0; i < game->bulletCount; i++)
        {
            Bullet* bullet = &game->bullets[i];
            updateBullet(bullet,deltaTime);
        }
		gameRemoveBullet(game);
		*/

		//test collision
		//testGameCollisions(game);

	}
	else
	{
		//TODO
		frameCount++;
	}
}

void runGameLoop(Game* game)
{
	while (!WindowShouldClose() && game->gameIsRunning) 
	{
		processInput(game);
		updateGame(game);
		drawGame(game);
	}
}
void drawGame(Game* game)
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	//drawGameBackground(game);

	if (!game->gamePaused)
	{
		//display all game objects

		//draw enemies
        /*for(int i = 0; i < ENEMY_COUNT; i++)
        {
            drawFloatingMine(&game->enemies[i],&game->gameTexture);
        }

		drawLayer(&game->layer,&game->gameTexture);

		drawPlayer(&game->player,&game->gameTexture);
		*/

		//draw bullets
        /*for(int i = 0; i < game->bulletCount; i++)
        {
            Bullet* bullet = &game->bullets[i];
            drawBullet(bullet,&game->gameTexture);
        }*/

		/*if(game->thisHasCollideWith)
		{
			DrawText("COLLISION",SCREEN_WIDTH / 2.0f - MeasureText("COLLISION",50) + 150.0f,
                SCREEN_HEIGHT / 2.0f,50,RED);
			game->thisHasCollideWith = false;
		}*/
	}
	else
	{
		//pauseGame(game);
	}

	EndDrawing();
}
void shutdown(Game* game)
{
	//unloadGameData(game);
	//game->gameIsRunning = false;
	//unloadGameData(game);
	//CloseWindow();
	//if (!game->gameIsRunning)
	//{
		//game->gameIsRunning = false;
		//unloadGameData(game);
		//CloseWindow();
	//}
}

void loadGameData(Game* game)
{
	/*game->background = LoadTexture("assets/background.png");
	game->foreground =  LoadTexture("assets/foreground.png");
	game->gameTexture = LoadTexture("assets/mines.png");*/
}
void unloadGameData(Game* game)
{
	/*UnloadTexture(game->background);
	UnloadTexture(game->foreground);
	UnloadTexture(game->gameTexture);*/
}

void drawGameBackground(Game* game)
{
	/*DrawTexture(game->background, 0, 0, WHITE);
	DrawTexture(game->foreground, 0, 0, WHITE);*/
}

void pauseGame(Game* game)
{
	if ((frameCount / 30) % 2) DrawText("GAME PAUSED",
		(int)SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED",50) + 200, (int)SCREEN_HEIGHT/2 -50,50,PURPLE);
}


/*void gameAddBullet(Game* game, Vector2 position)
{
    if(game->bulletCount == BULLET_CAPACITY)
    {
        return;
    }

    Bullet bullet = {0};

    //inti bullet
    initBullet(&bullet,position,game->player.rotation);
    
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
*/