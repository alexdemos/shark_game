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
    const int SCREEN_BUFFER = 200;
    int enemyAmount = 36;
    Color OCEAN = (Color){(unsigned char)3,(unsigned char)96,(unsigned char)186};

    BasicEnemy* enemies = malloc(sizeof(*enemies) * enemyAmount);
    Shark *shark = malloc(sizeof(*shark));
    World *world = malloc(sizeof(*world));
    Camera2D camera = { 0 };
    
    initWorld(world);
    initShark(shark, screenWidth, screenHeight);
    initEnemies(enemies, enemyAmount, world);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Image sharkImage = LoadImage("./assets/shark0.png");
    Texture2D sharkTexture = LoadTextureFromImage(sharkImage);
    SetTextureFilter(sharkTexture, TEXTURE_FILTER_TRILINEAR);
    UnloadImage(sharkImage);
    Image cloudImage = LoadImage("./assets/cloud.png");
    Texture2D cloudTexture = LoadTextureFromImage(cloudImage);
    SetTextureFilter(cloudTexture, TEXTURE_FILTER_TRILINEAR);
    UnloadImage(cloudImage);

    initCamera(&camera, shark);
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        handleCollisions(shark, enemies, enemyAmount, world);

        updateShark(shark, world);    
        updateEnemies(enemies, enemyAmount);
        updateCamera(&camera, shark, SCREEN_BUFFER);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(OCEAN);

            BeginMode2D(camera);
            drawWorld(world, cloudTexture, SCREEN_BUFFER);    
            drawEnemies(enemies,enemyAmount);
            drawShark(shark, sharkTexture);
            EndMode2D();

            drawUI(shark);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(sharkTexture);
    UnloadTexture(cloudTexture);
    CloseWindow();        // Close window and OpenGL context
    free(enemies);
    free(shark);
    free(world);
    //--------------------------------------------------------------------------------------

    return 0;
}
