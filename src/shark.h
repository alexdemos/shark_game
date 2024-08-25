#ifndef SHARK_H
#define SHARK_H
#include "raylib.h"
#include "world.h"

typedef struct Shark {
    Rectangle rectangle;
    int speed;
    float health;
    float xp;
    int level;
} Shark;

void initShark(Shark *shark, int screenW, int screenH);
void updateShark(Shark *shark, World *world);
void updateSharkHealth(Shark *shark, float amount);
void updateSharkPosition(Shark *shark, World *world);
void upgradeShark(Shark *shark, int enemySize);
void drawShark(Shark *traits);

#endif