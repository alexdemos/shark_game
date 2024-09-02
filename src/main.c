#include "enemies.h"
#include "shark.h"
#include "ui.h"
#include "world.h"
#include "camera.h"
#include "collisions.h"

#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

void loadSharkTextures(Texture2D *textures){
    Image sharkImageLeft = LoadImage("./assets/shark0l.png");
    textures[0] = LoadTextureFromImage(sharkImageLeft);
    SetTextureFilter(textures[0], TEXTURE_FILTER_TRILINEAR);
    UnloadImage(sharkImageLeft);
    Image sharkImageRight = LoadImage("./assets/shark0r.png");
    textures[1] = LoadTextureFromImage(sharkImageRight);
    SetTextureFilter(textures[1], TEXTURE_FILTER_TRILINEAR);
    UnloadImage(sharkImageRight);
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 3000;
    const int screenHeight = 1500;
    const int SCREEN_BUFFER = 400;
    int basicEnemyAmount = 24;
    int basicOffset = 0;
    int bigEnemyAmount = 12;
    int bigOffset = basicOffset + basicEnemyAmount;
    int totalEnemyAmount = basicEnemyAmount + bigEnemyAmount;
    Color OCEAN = (Color){(unsigned char)3,(unsigned char)96,(unsigned char)186};

    Enemy **enemies = malloc(sizeof(*enemies) * totalEnemyAmount); 
    Shark shark;
    World world;
    Camera2D camera = { 0 };
    
    world = initWorld();
    shark = initShark(screenWidth, screenHeight);
    initBasicEnemies(enemies, basicEnemyAmount, &world, basicOffset);
    initBigEnemies(enemies, bigEnemyAmount, &world, bigOffset);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D sharkTextures[2];
    loadSharkTextures(sharkTextures);
    Image cloudImage = LoadImage("./assets/cloud.png");
    Texture2D cloudTexture = LoadTextureFromImage(cloudImage);
    SetTextureFilter(cloudTexture, TEXTURE_FILTER_TRILINEAR);
    UnloadImage(cloudImage);

    initCamera(&camera, &shark);
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        handleCollisions(&shark, enemies, totalEnemyAmount, &world);

        updateShark(&shark, &world);    
        updateEnemies(enemies, totalEnemyAmount);
        updateCamera(&camera, &shark, SCREEN_BUFFER);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(OCEAN);

            BeginMode2D(camera);
            drawWorld(&world, cloudTexture, SCREEN_BUFFER);    
            drawEnemies(enemies,totalEnemyAmount);
            drawShark(&shark, sharkTextures);
            EndMode2D();

            drawUI(&shark);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(sharkTextures[0]);
    UnloadTexture(sharkTextures[1]);
    UnloadTexture(cloudTexture);
    CloseWindow();     // Close window and OpenGL context
    freeEnemies(enemies, totalEnemyAmount);
    free(enemies);
    //--------------------------------------------------------------------------------------

    return 0;
}
