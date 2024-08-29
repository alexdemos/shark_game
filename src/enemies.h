#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <stdbool.h>
#include "world.h"
#include "raylib.h"

typedef struct BasicEnemy {
    Rectangle rectangle;
    int origin[2];
    int range;
    int speed;
    Color color;
    int xp;
    int healthGiven;
    bool seesPlayer;
} BasicEnemy;

void updateEnemy(BasicEnemy *enemy);
void updateEnemies(BasicEnemy *enemies, int amount);

void drawEnemy(BasicEnemy *enemy);
void drawEnemies(BasicEnemy *enemies, int amount);

void recycleEnemy(BasicEnemy *enemy, World *world);
void initEnemies(BasicEnemy *buffer, int amount, World *world);
Vector2 getRandomPosition(World *world, BasicEnemy *enemy);

#endif