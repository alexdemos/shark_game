#include "enemies.h"
#include "shark.h"
#include "ui.h"
#include "world.h"
#include "camera.h"
#include "collisions.h"

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
    World *world = malloc(sizeof(*world));
    Camera2D camera = { 0 };
    
    initShark(shark, screenWidth, screenHeight);
    initEnemies(enemies, enemyAmount);
    initWorld(world);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    initCamera(&camera, shark);
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        handleCollisions(shark, enemies, enemyAmount);

        updateShark(shark, world);    
        updateEnemies(enemies, enemyAmount);

        updateCamera(&camera, shark);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(SKYBLUE);

            BeginMode2D(camera);
            drawShark(shark);
            drawEnemies(enemies,enemyAmount);
            EndMode2D();

            drawUI(shark);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    free(enemies);
    free(shark);
    free(world);
    //--------------------------------------------------------------------------------------

    return 0;
}
