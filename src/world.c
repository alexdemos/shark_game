#include "world.h"

#include "raylib.h"

const int TRIANGLE_AMOUNT = 4;

void initWorld(World *world){
    world->GROUND = 4000;
    world->SURFACE = -4000;
    world->LEFT = -4000;
    world->RIGHT = 4000;
}

void drawWorld(World *world, Texture2D cloudTexture, int SCREEN_BUFFER){
    drawBackgroundTriangles(world, TRIANGLE_AMOUNT);
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
    drawClouds(world, cloudTexture, SCREEN_BUFFER);
}

void drawBackgroundTriangles(World *world, int amount){
    int i;
    int worldLength = world->RIGHT - world->LEFT;
    float triangleWidth = worldLength / amount;

    for (i=0; i < amount; i++){
        DrawTriangle((Vector2){world->LEFT + (i * triangleWidth), world->GROUND}, 
                    (Vector2){world->LEFT + ((i+1) * triangleWidth), world->GROUND},
                    (Vector2){world->LEFT + (i * triangleWidth) + (triangleWidth/2), world->SURFACE+1000},
                    BLUE);
    }
}

void drawClouds(World *world, Texture2D cloudTexture, int SCREEN_BUFFER){
    Rectangle source = (Rectangle){0.0f,0.0f,100.0f,61.0f};
    float cloudWidth = 200.0f;
    float cloudHeight = 122.0f;
    int cloudAmount = (world->RIGHT - world->LEFT) / cloudWidth;
    int spacing = 800;
    int i;
    for(i = 0; i < cloudAmount; i++){
        Rectangle destination = (Rectangle){world->LEFT + (i* (cloudWidth + spacing)), 
                                world->SURFACE-(SCREEN_BUFFER/2) - (i%2)*50,
                                cloudWidth, cloudHeight};
        DrawTexturePro(cloudTexture, source, destination, (Vector2){0,0}, 0, WHITE);
    }
}