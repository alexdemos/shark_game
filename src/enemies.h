#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <stdbool.h>
#include "world.h"
#include "raylib.h"

typedef struct Enemy {
    Rectangle rectangle;
    int origin[2];
    int range;
    int speed;
    Color color;
    int xp;
    int healthGiven;
    bool seesPlayer;
} Enemy;

void updateEnemy(Enemy *enemy);
void updateEnemies(Enemy **enemies, int amount);

void drawEnemy(Enemy *enemy);
void drawEnemies(Enemy **enemies, int amount);

void recycleEnemy(Enemy *enemy, World *world);
void initBasicEnemies(Enemy **enemies, int amount, World *world);
Vector2 getRandomPosition(World *world, Enemy *enemy);

void freeEnemies(Enemy **enemies, int amount);

#endif