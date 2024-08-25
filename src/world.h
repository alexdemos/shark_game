#ifndef WORLD_H_
#define WORLD_H_

typedef struct World{
    int GROUND;
    int SURFACE;
    int LEFT;
    int RIGHT; 
} World;

void initWorld(World *world);

#endif