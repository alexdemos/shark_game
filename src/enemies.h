#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <stdbool.h>
#include "raylib.h"

typedef struct BasicEnemy {
    int x;
    int y;
    int origin[2];
    int range;
    int size;
    int speed;
    Color color;
    bool seesPlayer;
} BasicEnemy;

void updateEnemy(BasicEnemy *enemy);
void updateEnemies(BasicEnemy *enemies, int amount);

void drawEnemy(BasicEnemy *enemy);
void drawEnemies(BasicEnemy *enemies, int amount);

void initEnemies(BasicEnemy *buffer, int amount);

#endif