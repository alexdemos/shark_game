#include "shark.h"
#include "enemies.h"
#include "collisions.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void processCollision(Shark *shark, Enemy *enemy, World *world){
    if(shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark, enemy->xp, enemy->healthGiven);
        recycleEnemy(enemy, world);
    }
}

void handleCollisions(Shark *shark, struct Enemy **enemies, int enemyAmount, World *world){
    int i;
    for(i=0; i < enemyAmount; i++){
        Enemy *enemy = enemies[i];
        if(CheckCollisionRecs(shark->rectangle, enemy->rectangle)){
            processCollision(shark, enemy, world);
        } 
    }
}
