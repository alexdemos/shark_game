#include "enemies.h"
#include "world.h"
#include "raylib.h"

#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void initBasicEnemies(Enemy **enemies, int amount, World *world, int offset){
    int i;
    for (i=offset; i<amount+offset; i++) {
        Enemy *enemy = malloc(sizeof(*enemy));
        enemy->range[0] = 250.0f;
        enemy->range[1] = 75.0f; 
        enemy->habitat[0] = 0;
        enemy->habitat[1] = world->RIGHT/2;
        enemy->depth[0] = world->SURFACE;
        enemy->depth[1] = world->SURFACE + 1000;
        enemy->rectangle.height = 30;
        enemy->rectangle.width = 60;
        Vector2 pos = getRandomPosition(world, enemy);
        enemy->rectangle.x = pos.x;
        enemy->rectangle.y = pos.y;
        enemy->origin[0] = enemy->rectangle.x;
        enemy->origin[1] = enemy->rectangle.y;
        enemy->speed[0] = rand()%3+1;
        enemy->speed[1] = rand()%3+1;
        enemy->color = RED;
        enemy->xp = 10;
        enemy->healthGiven = 5;
        enemy -> damage = 2;
        enemy->seesPlayer = false;
        enemies[i] = enemy;
    }
}

void initBigEnemies(Enemy **enemies, int amount, World *world, int offset){
    int i;
    for (i=offset; i<amount+offset; i++) {
        Enemy *enemy = malloc(sizeof(*enemy));
        enemy->range[0] = 250.0f;
        enemy->range[1] = 75.0f; 
        enemy->habitat[0] = 2000;
        enemy->habitat[1] = world->RIGHT;
        enemy->depth[0] = world->SURFACE + 1000;
        enemy->depth[1] = world->SURFACE + 2000;
        enemy->rectangle.height = 100;
        enemy->rectangle.width = 100;
        Vector2 pos = getRandomPosition(world, enemy);
        enemy->rectangle.x = pos.x;
        enemy->rectangle.y = pos.y;
        enemy->origin[0] = enemy->rectangle.x;
        enemy->origin[1] = enemy->rectangle.y;
        enemy->speed[0] = rand()%3+1;
        enemy->speed[1] = rand()%3+1;
        enemy->color = PURPLE;
        enemy->xp = 20;
        enemy->healthGiven = 10;
        enemy->damage = -5;
        enemy->seesPlayer = false;
        enemies[i] = enemy;
    }
}

void updateEnemy(Enemy *enemy){
    if (!enemy->seesPlayer){
        if (enemy->rectangle.x > enemy->range[0] + enemy->origin[0] ||
            enemy->rectangle.x < enemy->origin[0]){
                enemy->speed[0] *= -1;
            }
        if (enemy->rectangle.y > enemy->range[1] + enemy->origin[1] || 
            enemy->rectangle.y < enemy->origin[1]){
                enemy->speed[1] *= -1;
        }
        enemy->rectangle.x += enemy->speed[0];
        enemy->rectangle.y += enemy->speed[1];
    }
}

void updateEnemies(Enemy **enemies, int amount){
    int i;
    for (i=0; i<amount; i++) {
        updateEnemy(enemies[i]);
    }
}

void *pauseEnemyThread(void *threadArg){
    Enemy *enemy;
    enemy = (Enemy*) threadArg;
    int original_x = enemy->speed[0];
    int original_y = enemy->speed[1];
    enemy->speed[0] = 0;
    enemy->speed[1] = 0;
    sleep(1);
    enemy->speed[0] = original_x;
    enemy->speed[1] = original_y;
    return threadArg;
}

void pauseEnemy(Enemy *enemy){
    //if speed is 0, we've already started a thread
    if(enemy->speed[0] != 0 && enemy->speed[1] != 0){
        pthread_t threadId;
        pthread_create(&threadId, NULL, pauseEnemyThread, (void*)enemy);
        pthread_detach(threadId);
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
    int negative[2] = {-1,1};
    Vector2 pos = {((rand() % (enemy->habitat[1] - enemy->habitat[0] - (int)enemy->range[0] - (int)enemy->rectangle.width)) 
                    + enemy->habitat[0]) * negative[rand()%2],
                   (rand() % (enemy->depth[1] - enemy->depth[0] - (int)enemy->range[1] - (int)enemy->rectangle.height)) 
                    + enemy->depth[0]};
    return pos;
}

void freeEnemies(Enemy **enemies, int amount){
    int i;
    for(i=0; i < amount; i++){
        free(enemies[i]);
    }
}
