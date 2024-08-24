#include "enemies.h"
#include "shark.h"
#include "ui.h"
#include "world.h"

#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int enemyAmount = 3;

    BasicEnemy* enemies = malloc(sizeof(*enemies) * enemyAmount);
    Shark *shark = malloc(sizeof(*shark));
    
    initShark(shark);
    initEnemies(enemies, enemyAmount);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        handleCollisions(shark, enemies, enemyAmount, screenWidth, screenHeight);
        updateSharkPosition(shark);
        updateEnemies(enemies, enemyAmount);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawShark(shark);
            drawEnemies(enemies,enemyAmount);
            drawHealthBar(shark->health);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    free(enemies);
    free(shark);
    //--------------------------------------------------------------------------------------

    return 0;
}
