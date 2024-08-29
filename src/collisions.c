#include "shark.h"
#include "enemies.h"
#include "collisions.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void processCollision(Shark *shark, BasicEnemy *enemy, World *world){
    if(shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark, enemy->xp);
        recycleEnemy(enemy, world);
    }
}

void handleCollisions(Shark *shark, struct BasicEnemy *enemies, int enemyAmount, World *world){
    int i;
    for(i=0; i < enemyAmount; i++){
        BasicEnemy *enemy = &enemies[i];
        if(CheckCollisionRecs(shark->rectangle, enemy->rectangle)){
            processCollision(shark, enemy, world);
        } 
    }
}
