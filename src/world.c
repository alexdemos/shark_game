#include "world.h"
#include "shark.h"
#include "enemies.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void handleCollisions(Shark *shark, struct BasicEnemy *enemies, int enemyAmount){
    int i;
    for(i=0; i < enemyAmount; i++){
        BasicEnemy *enemy = &enemies[i];
        if(CheckCollisionRecs(shark->rectangle, enemy->rectangle)){
            processCollision(shark, enemy);
        } 
    }
}

void processCollision(Shark *shark, BasicEnemy *enemy){
    if(shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark, enemy->rectangle.height * enemy->rectangle.width);
        recycleEnemy(enemy);
    }
}