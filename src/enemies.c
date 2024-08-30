#include "enemies.h"
#include "world.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void initBasicEnemies(Enemy **enemies, int amount, World *world){
    int i;
    for (i=0; i<amount; i++) {
        Enemy *enemy = malloc(sizeof(*enemy));
        enemy->range = 175;
        Vector2 pos = getRandomPosition(world, enemy);
        enemy->rectangle.x = pos.x;
        enemy->rectangle.y = pos.y;
        enemy->rectangle.height = 30;
        enemy->rectangle.width = 60;
        enemy->origin[0] = enemy->rectangle.x;
        enemy->origin[1] = enemy->rectangle.y;
        enemy->speed = 2;
        enemy->color = RED;
        enemy->xp = 10;
        enemy->healthGiven = 5;
        enemy->seesPlayer = false;
        enemies[i] = enemy;
    }
}

void updateEnemy(Enemy *enemy){
    if (!enemy->seesPlayer){
        if (enemy->rectangle.x > enemy->origin[0]+enemy->range || enemy->rectangle.x < enemy->origin[0]){
            enemy->speed *= -1;
        } 
        enemy->rectangle.x += enemy->speed;
    }
}

void updateEnemies(Enemy **enemies, int amount){
    int i;
    for (i=0; i<amount; i++) {
        updateEnemy(enemies[i]);
    }
}

void drawEnemy(Enemy *enemy){
    DrawRectangleRec(enemy->rectangle,enemy->color);
}

void drawEnemies(Enemy **enemies, int amount){
    int i;  
    for (i=0; i<amount; i++) {
        drawEnemy(enemies[i]);  
    }
}

void recycleEnemy(Enemy *enemy, World *world){
    Vector2 pos = getRandomPosition(world, enemy);
    enemy->rectangle.x = pos.x;
    enemy->rectangle.y = pos.y;
    enemy->origin[0] = enemy->rectangle.x;
    enemy->origin[1] = enemy->rectangle.y;
}

Vector2 getRandomPosition(World *world, Enemy *enemy){
    //makes sure enemies don't clip into right wall
    Vector2 pos = {(rand() % (world->RIGHT - world->LEFT - enemy->range)) - world->RIGHT,
                   (rand() % (world->GROUND - world->SURFACE)) - world->GROUND};
    return pos;
}

void freeEnemies(Enemy **enemies, int amount){
    int i;
    for(i=0; i < amount; i++){
        free(enemies[i]);
    }
}
