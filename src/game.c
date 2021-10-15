#include "game.h"

static int framesCounter = 0;
bool initGame(Game* game)
{
    game->gameIsRunning = true;
    game->gamePaused = false;
    
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"VICTOR-MATHIEU-OSVALDO");
    SetTargetFPS(60);

    //Init Player
    initPlayer(&game->player);

    //inti ememies
    //for(int i = 0; i < ENEMY_COUNT; i++)
    //{
        //initEnemy(&game->enemies[i]);
    //}

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
        updteGame(game);
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
void updteGame(Game* game)
{
    game->ticksCount = GetFrameTime();
    if(!game->gamePaused)
    {
        //update all objects in game
        updatePlayer(&game->player,game->ticksCount);

        //update enemies
        //for(int i = 0; i < ENEMY_COUNT; i++)
        //{
            //updateEnemy(&game->enemies[i],game->ticksCount);
        //}

        //update bullets
        //for(int i = 0; i < game->bulletCount; i++)
        //{
            //Bullet* bullet = &game->bullets[i];
            //updateBullet(bullet,game->ticksCount);
        //}
        //gameRemoveBullet(game);

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

    if(!game->gamePaused)
    {

        //draw enemies
        //for(int i = 0; i < ENEMY_COUNT; i++)
        //{
            //drawEnemy(&game->enemies[i]);
        //}

        //draw bullets
        //for(int i = 0; i < game->bulletCount; i++)
        //{
            //Bullet* bullet = &game->bullets[i];
            //drawBullet(bullet);
        //}

        //draw Player
        drawPlayer(&game->player);
    }
   
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

            unloadBulletData(bullet);
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
    //load player data
    loadPlayerData(&game->player);

    //load enemy data
    //for(int i = 0; i < ENEMY_COUNT; i++)    for(int i = 0; i < ENEMY_COUNT; i++)
    //{
        //initEnemy(&game->enemies[i]);
    //}
}
void unloadData(Game* game)
{
    unloadPlayerdata(&game->player);

    for(int i = 0; i < ENEMY_COUNT; i++)
    {
        unLoadEnemyData(&game->enemies[i]);
    }
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