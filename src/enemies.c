#include "enemies.h"
#include "raylib.h"
#include <stdbool.h>

void initEnemies(BasicEnemy *buffer, int amount){
    int i;
    for (i=0; i<amount; i++) {
        BasicEnemy enemy = {100*(i+1), 100*(i+1), {100*(i+1),100*(i+1)}, 175, 10, 2, RED, false};
        buffer[i] = enemy;
    }
}

void updateEnemy(BasicEnemy *enemy){
    if (!enemy->seesPlayer){
        if (enemy->x > enemy->origin[0]+enemy->range || enemy->x < enemy->origin[0]){
            enemy->speed *= -1;
        } 
        enemy->x += enemy->speed;
    }
}

void updateEnemies(BasicEnemy *enemies, int amount){
    int i;
    for (i=0; i<amount; i++) {
        updateEnemy(&enemies[i]);
    }
}

void drawEnemy(BasicEnemy *enemy){
    DrawCircle(enemy->x,enemy->y,enemy->size,enemy->color);
}

void drawEnemies(BasicEnemy *enemies, int amount){
    int i;  
    for (i=0; i<amount; i++) {
        drawEnemy(&enemies[i]);  
    }
}
