#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "shark.h"
#include "enemies.h"

void processCollision(Shark *shark, Enemy *enemy, World *world);
void handleCollisions(Shark *shark, Enemy **enemies, int enemyAmount, World *world);

#endif