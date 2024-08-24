#include "world.h"
#include "shark.h"
#include "enemies.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void handleCollisions(Shark *shark, struct BasicEnemy *enemies, int enemyAmount, int screenW, int screenH){
    int i;
    for(i=0; i < enemyAmount; i++){
        BasicEnemy *enemy = &enemies[i];
        if(CheckCollisionRecs(shark->rectangle, enemy->rectangle)){
            processCollision(shark, enemy, screenW, screenH);
        } 
    }
}

void processCollision(Shark *shark, BasicEnemy *enemy, int screenW, int screenH){
    if(shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark);
        recycleEnemy(enemy, screenW, screenH);
    }
}