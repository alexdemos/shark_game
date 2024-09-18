#ifndef SHARK_H
#define SHARK_H
#include "raylib.h"
#include "world.h"
#include <stdbool.h>

typedef struct Shark {
    Rectangle rectangle;
    float speed;
    int direction;  //0 is left, 1 is right
    int rotation;
    float health;
    int xp;
    int level;
    bool is_invinvible;
} Shark;

Shark initShark();

void updateShark(Shark *shark, World *world);
void updateSharkHealth(Shark *shark, float amount);
void updateSharkPosition(Shark *shark, World *world);
void makeInvincible(Shark *shark);
void *makeInvincibleThread(void *threadArg);

void upgradeShark(Shark *shark, int enemyXp, float health);
float calculateNextLevelXp(int level);

void drawShark(Shark *traits, Texture2D *texture);
void levelUp(Shark *shark);

#endif