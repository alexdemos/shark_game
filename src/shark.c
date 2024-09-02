#include "shark.h"
#include "world.h"

#include "raylib.h"
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

Shark initShark(int screenW, int screenH){
    Shark shark;
    shark.rectangle.x = 0.0f;
    shark.rectangle.y = 0.0f;
    shark.rectangle.width = 100.0f;
    shark.rectangle.height = 50.0f;
    shark.direction = 0;
    shark.rotation = 0;
    shark.speed = 10.0f;
    shark.health = 100;
    shark.xp = 0;
    shark.level = 1;
    shark.is_invinvible = false;

    return shark;
}

void updateShark(Shark *shark, World *world){
    updateSharkPosition(shark, world);
    updateSharkHealth(shark, -.05);
}

void updateSharkPosition(Shark *shark, World *world){
    if(IsKeyDown(KEY_RIGHT)) {
        shark->rectangle.x += shark->speed;
        shark->direction = 1;
    }
    if(IsKeyDown(KEY_LEFT)) { 
        shark->rectangle.x -= shark->speed;
        shark->direction = 0;
    }
    if(IsKeyDown(KEY_UP)) shark->rectangle.y -= shark->speed;
    if(IsKeyDown(KEY_DOWN)) shark->rectangle.y += shark->speed;
    if(shark->rectangle.x < world->LEFT) shark->rectangle.x = world->LEFT;
    if(shark->rectangle.x + shark->rectangle.width > world->RIGHT) shark->rectangle.x = world->RIGHT - shark->rectangle.width;
    if(shark->rectangle.y + shark->rectangle.height> world->GROUND) shark->rectangle.y = world->GROUND - shark->rectangle.height;
    if(shark->rectangle.y < world->SURFACE) shark->rectangle.y = world->SURFACE;
}

void *makeInvincibleThread(void *threadArg){
    Shark *shark;
    shark = (Shark*) threadArg;
    shark->is_invinvible = true;
    sleep(3);
    shark->is_invinvible = false;
    return threadArg;
}

void makeInvincible(Shark *shark){
    if (!shark->is_invinvible){
        pthread_t threadId;
        pthread_create(&threadId, NULL, makeInvincibleThread, (void*)shark);
        pthread_detach(threadId);
    }
}

void updateSharkHealth(Shark *shark, float amount){
    if (amount > 0 || !shark->is_invinvible){
        float newHealth = shark->health + amount;
        if(newHealth > 100){
            newHealth = 100;
        } else if(newHealth < 0){
            newHealth = 0;
        }
        shark->health = newHealth;
    }
    if(amount <= -1){
        makeInvincible(shark);
    }
}

void upgradeShark(Shark *shark, int enemyXp, float health){
    shark->xp += enemyXp;
    int nextLevelXp = calculateNextLevelXp(shark->level);
    if(shark->xp >= nextLevelXp){ 
        shark->xp = shark->xp % nextLevelXp;
        shark->level ++;
        levelUp(shark);
    }
    updateSharkHealth(shark, health);
}

void drawShark(Shark *shark, Texture2D *texture){
    Color tint = WHITE;
    if (shark->is_invinvible){
        tint = BLUE;
    }
    //Vector2 origin = (Vector2){shark->rectangle.width/2,shark->rectangle.height/2};
    Vector2 origin = (Vector2){0,0};
    DrawRectangleRec(shark->rectangle, GRAY);
    DrawTexturePro(texture[shark->direction], (Rectangle){0.0f,0.0f,33.0f,19.0f}, shark->rectangle, 
                origin,shark->rotation, tint);
}

//returns float so drawing xp bar works
float calculateNextLevelXp(int level){
    return level * 100;
}

void levelUp(Shark *shark){
    shark->speed *= 1.05;
    shark->rectangle.width *= 1.05;
    shark->rectangle.height *= 1.05;
}