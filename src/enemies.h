#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <stdbool.h>
#include "world.h"
#include "raylib.h"

typedef struct Enemy {
    Rectangle rectangle;
    Color color;
    float origin[2]; //1st x origin; 2nd y origin
    float range[2]; //1st x range; 2nd y range
    int habitat[2]; //1st start to spawn; 2nd end spawn 
    int depth[2]; //1st min depth; 2nd max depth
    float speed[2];
    int xp;
    float healthGiven;
    float damage;
    bool seesPlayer;
} Enemy;

void updateEnemy(Enemy *enemy);
void updateEnemies(Enemy **enemies, int amount);
void pauseEnemy(Enemy *enemy);
void *pauseEnemyThread(void *enemy);

void drawEnemy(Enemy *enemy);
void drawEnemies(Enemy **enemies, int amount);

void recycleEnemy(Enemy *enemy, World *world);

void initBasicEnemies(Enemy **enemies, int amount, World *world, int offset);
void initBigEnemies(Enemy **enemies, int amount, World *world, int offset);

Vector2 getRandomPosition(World *world, Enemy *enemy);

void freeEnemies(Enemy **enemies, int amount);

#endif