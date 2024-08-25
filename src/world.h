#ifndef WORLD_H_
#define WORLD_H_
#include "enemies.h"
#include "shark.h"

void handleCollisions(Shark *shark, BasicEnemy *enemies, int enemyAmount);
void processCollision(Shark *shark, BasicEnemy *enemy);

#endif