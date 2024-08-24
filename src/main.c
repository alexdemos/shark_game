#include "enemies.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>


/***  data ***/
struct SharkTraits {
        int x;
        int y;
        int size;
        int speed;
        int health;
};

void updateSharkPosition(struct SharkTraits *traits){
    if(IsKeyDown(KEY_RIGHT)) traits->x += traits->speed;
    if(IsKeyDown(KEY_LEFT)) traits->x -= traits->speed;
    if(IsKeyDown(KEY_UP)) traits->y -= traits->speed;
    if(IsKeyDown(KEY_DOWN)) traits->y += traits->speed;
}

void drawHealthBar(int health){
    int i;
    int screenWidth = GetScreenWidth();
    for (i = 1; i <= health; i++){
        DrawCircle(screenWidth - (30*i), 10, 10, RED);
    }
}

void drawShark(struct SharkTraits *traits){
    DrawRectangle(traits->x, traits->y, traits->size, traits->size / 2, BLUE);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    struct SharkTraits shark_traits = {1000, 500, 50,2,3};
    BasicEnemy** enemies = malloc(sizeof(BasicEnemy) * 3);
    initEnemies(enemies, 3);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        updateSharkPosition(&shark_traits);
        updateEnemies(enemies,3);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawShark(&shark_traits);
            drawEnemies(enemies,3);
            drawHealthBar(shark_traits.health);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    free(enemies);
    //--------------------------------------------------------------------------------------

    return 0;
}
