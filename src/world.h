#ifndef WORLD_H_
#define WORLD_H_
#include "raylib.h"

typedef struct World{
    int GROUND;
    int SURFACE;
    int LEFT;
    int RIGHT; 
} World;

void initWorld(World *world);
void drawWorld(World *world, Texture2D cloudTexture, int SCREEN_BUFER);
void drawBackgroundTriangles(World *world, int amount);
void drawClouds(World *world, Texture2D cloudTexture, int SCREEN_BUFFER);

#endif