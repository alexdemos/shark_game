#ifndef WORLD_H_
#define WORLD_H_
#include "enemies.h"
#include "shark.h"

void handleCollisions(Shark *shark, BasicEnemy *enemies, int enemyAmount, int screenW, int screenH);
void processCollision(Shark *shark, BasicEnemy *enemy, int screenW, int screenH);

#endif