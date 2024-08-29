#ifndef SHARK_H
#define SHARK_H
#include "raylib.h"
#include "world.h"

typedef struct Shark {
    Rectangle rectangle;
    float speed;
    float health;
    int xp;
    int level;
} Shark;

void initShark(Shark *shark, int screenW, int screenH);
void updateShark(Shark *shark, World *world);
void updateSharkHealth(Shark *shark, float amount);
void updateSharkPosition(Shark *shark, World *world);
void upgradeShark(Shark *shark, int enemyXp, int health);
void drawShark(Shark *traits, Texture2D texture);
float calculateNextLevelXp(int level);
void levelUp(Shark *shark);

#endif