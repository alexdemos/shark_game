#include "shark.h"
#include "world.h"

#include "raylib.h"

void initShark(Shark *shark, int screenW, int screenH){
    shark->rectangle.x = screenW / 2.0f;
    shark->rectangle.y = screenH / 2.0f;
    shark->rectangle.width = 50.0f;
    shark->rectangle.height = 25.0f;
    shark->speed = 4;
    shark->health = 100;
    shark->xp = 0;
    shark->level = 1;
}

void updateShark(Shark *shark, World *world){
    updateSharkPosition(shark, world);
    updateSharkHealth(shark, -.05);
}

void updateSharkPosition(Shark *shark, World *world){
    if(IsKeyDown(KEY_RIGHT)) shark->rectangle.x += shark->speed;
    if(IsKeyDown(KEY_LEFT)) shark->rectangle.x -= shark->speed;
    if(IsKeyDown(KEY_UP)) shark->rectangle.y -= shark->speed;
    if(IsKeyDown(KEY_DOWN)) shark->rectangle.y += shark->speed;
    if(shark->rectangle.x < world->LEFT) shark->rectangle.x = world->LEFT;
    if(shark->rectangle.x > world->RIGHT) shark->rectangle.x = world->RIGHT;
    if(shark->rectangle.y > world->GROUND) shark->rectangle.y = world->GROUND;
    if(shark->rectangle.y < world->SURFACE) shark->rectangle.y = world->SURFACE;
}

void updateSharkHealth(Shark *shark, float amount){
    float newHealth = shark->health + amount;
    if(newHealth > 100){
        newHealth = 100;
    } else if(newHealth < 0){
        newHealth = 0;
    }
    shark->health = newHealth;
}

void upgradeShark(Shark *shark, int enemySize){
    shark->xp += enemySize/100;
    updateSharkHealth(shark, 5);
}

void drawShark(Shark *shark){
    DrawRectangleRec(shark->rectangle, GRAY);
}