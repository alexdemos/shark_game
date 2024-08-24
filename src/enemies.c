#include "enemies.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>

void initEnemies(BasicEnemy *buffer, int amount){
    int i;
    for (i=0; i<amount; i++) {
        BasicEnemy *enemy = malloc(sizeof(*enemy));
        enemy->rectangle.x = 100 * (i+1);
        enemy->rectangle.y = 100 * (i+1);
        enemy->rectangle.height = 10;
        enemy->rectangle.width = 20;
        enemy->origin[0] = enemy->rectangle.x;
        enemy->origin[1] = enemy->rectangle.y;
        enemy->range = 175;
        enemy->speed = 2;
        enemy->color = RED;
        enemy->seesPlayer = false;
        buffer[i] = *enemy;
    }
}

void updateEnemy(BasicEnemy *enemy){
    if (!enemy->seesPlayer){
        if (enemy->rectangle.x > enemy->origin[0]+enemy->range || enemy->rectangle.x < enemy->origin[0]){
            enemy->speed *= -1;
        } 
        enemy->rectangle.x += enemy->speed;
    }
}

void updateEnemies(BasicEnemy *enemies, int amount){
    int i;
    for (i=0; i<amount; i++) {
        updateEnemy(&enemies[i]);
    }
}

void drawEnemy(BasicEnemy *enemy){
    DrawRectangleRec(enemy->rectangle,enemy->color);
}

void drawEnemies(BasicEnemy *enemies, int amount){
    int i;  
    for (i=0; i<amount; i++) {
        drawEnemy(&enemies[i]);  
    }
}

void recycleEnemy(BasicEnemy *enemy, int screenW, int screenH){
    enemy->rectangle.x = rand() % screenW;
    enemy->rectangle.y = rand() % screenH;
    enemy->origin[0] = enemy->rectangle.x;
    enemy->origin[1] = enemy->rectangle.y;
}
