#include "world.h"

#include "raylib.h"

void initWorld(World *world){
    world->GROUND = 2000;
    world->SURFACE = -2000;
    world->LEFT = -2000;
    world->RIGHT = 2000;
}

void drawWorld(World *world, Texture2D cloudTexture, int SCREEN_BUFFER){
    //draw left wall
    DrawRectangle(world->LEFT - SCREEN_BUFFER, world->SURFACE, 
                SCREEN_BUFFER, world->GROUND - world->SURFACE + SCREEN_BUFFER, BROWN);
    //draw right wall
    DrawRectangle(world->RIGHT, world->SURFACE, 
                SCREEN_BUFFER, world->GROUND - world->SURFACE + SCREEN_BUFFER, BROWN);
    //draw ground
    DrawRectangle(world->LEFT - SCREEN_BUFFER, world->GROUND, 
                world->RIGHT - world->LEFT + (2 * SCREEN_BUFFER),SCREEN_BUFFER, GRAY);
    //draw sky
    DrawRectangle(world->LEFT - SCREEN_BUFFER, world->SURFACE - SCREEN_BUFFER, 
                world->RIGHT - world->LEFT + (2 * SCREEN_BUFFER),SCREEN_BUFFER, SKYBLUE);

    //draw cloud
    Rectangle cloud = (Rectangle){0.0f, world->SURFACE-100, 100.0f, 61.0f};
    DrawTexturePro(cloudTexture, (Rectangle){0.0f,0.0f,100.0f,61.0f}, cloud, (Vector2){0,0},0, WHITE);
}