#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "raylib.h"
#include "shark.h"
#include "enemies.h"

void processCollision(Shark *shark, Enemy *enemy, World *world);
void handleCollisions(Shark *shark, Enemy **enemies, int enemyAmount, World *world);
bool checkCollision(Shark *shark, Rectangle enemy);
Vector2 rotate(Vector2 point, Vector2 origin, double angle);

#endif