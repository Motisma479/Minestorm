#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
/***********************************\
Made by : Robion Mathieu
last edit: 15/10/2021
Desc:
    File to test save systeme
    The save saves position of player
\***********************************/

void save(){
//load the file
    FILE* dbFile = fopen("pk_db.csv", "r");
    if (dbFile == NULL)//cant't open the
    {
        printf("Cannot open pk_db.csv\n");
        return 1;
    }
//loading end
}


///////////////////////////////////////////////////////////////////////////////////////////
//                             Block to test a save methode                              //
///////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////