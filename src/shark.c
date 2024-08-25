#include "shark.h"
#include "raylib.h"

void initShark(Shark *shark, int screenW, int screenH){
    shark->rectangle.x = screenW / 2;
    shark->rectangle.y = screenH / 2;
    shark->rectangle.width = 50;
    shark->rectangle.height = 25;
    shark->speed = 4;
    shark->health = 100;
    shark->xp = 0;
    shark->level = 1;
}

void updateShark(Shark *shark){
    updateSharkPosition(shark);
    updateSharkHealth(shark, -.05);
}

void updateSharkPosition(Shark *shark){
    if(IsKeyDown(KEY_RIGHT)) shark->rectangle.x += shark->speed;
    if(IsKeyDown(KEY_LEFT)) shark->rectangle.x -= shark->speed;
    if(IsKeyDown(KEY_UP)) shark->rectangle.y -= shark->speed;
    if(IsKeyDown(KEY_DOWN)) shark->rectangle.y += shark->speed;
}

void updateSharkHealth(Shark *shark, float amount){
    float newHealth = shark->health + amount;
    if(newHealth > 100){
        newHealth = 100;
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