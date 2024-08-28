#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "shark.h"
#include "enemies.h"

void processCollision(Shark *shark, BasicEnemy *enemy, World *world);
void handleCollisions(Shark *shark, BasicEnemy *enemies, int enemyAmount, World *world);

#endif