#include "world.h"

#include "raylib.h"

void initWorld(World *world){
    world->GROUND = 1100;
    world->SURFACE = -200;
    world->LEFT = -200;
    world->RIGHT = 2000;
}