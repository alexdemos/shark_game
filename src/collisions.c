#include "shark.h"
#include "enemies.h"
#include "collisions.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void processCollision(Shark *shark, Enemy *enemy, World *world){
    if (shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark, enemy->xp, enemy->healthGiven);
        recycleEnemy(enemy, world);
    } else {
        upgradeShark(shark, 0, enemy->damage);
        pauseEnemy(enemy);
    }
}

void handleCollisions(Shark *shark, Enemy **enemies, int enemyAmount, World *world){
    int i;
    Rectangle collider = (Rectangle){shark->rectangle.x-shark->rectangle.width/2,
                                shark->rectangle.y-shark->rectangle.height/2,
                                shark->rectangle.width,
                                shark->rectangle.height};
    for(i=0; i < enemyAmount; i++){
        if(CheckCollisionRecs(collider, enemies[i]->rectangle)){
            processCollision(shark, enemies[i], world);
        } 
    }
}
