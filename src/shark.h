#ifndef SHARK_H
#define SHARK_H
#include "raylib.h"

typedef struct Shark {
    Rectangle rectangle;
    int speed;
    int health;
} Shark;

void initShark(Shark *shark);
void updateSharkPosition(struct Shark *shark);
void upgradeShark(struct Shark *shark);
void drawShark(struct Shark *traits);

#endif