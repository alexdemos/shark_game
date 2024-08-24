#ifndef ENEMIES_H_
#define ENEMIES_H_
#include <stdbool.h>
#include "raylib.h"

typedef struct BasicEnemy {
    Rectangle rectangle;
    int origin[2];
    int range;
    int speed;
    Color color;
    bool seesPlayer;
} BasicEnemy;

void updateEnemy(BasicEnemy *enemy);
void updateEnemies(BasicEnemy *enemies, int amount);

void drawEnemy(BasicEnemy *enemy);
void drawEnemies(BasicEnemy *enemies, int amount);

void recycleEnemy(BasicEnemy *enemy, int screenW, int screenH);

void initEnemies(BasicEnemy *buffer, int amount);

#endif