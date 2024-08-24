#include "shark.h"
#include "raylib.h"

void initShark(Shark *shark){
    float x = 1000;
    float y = 500;
    float w = 50;
    float h = 25;
    shark->rectangle.x = x;
    shark->rectangle.y = y;
    shark->rectangle.width = w;
    shark->rectangle.height = h;
    shark->speed = 4;
    shark->health = 3;
}

void updateSharkPosition(Shark *shark){
    if(IsKeyDown(KEY_RIGHT)) shark->rectangle.x += shark->speed;
    if(IsKeyDown(KEY_LEFT)) shark->rectangle.x -= shark->speed;
    if(IsKeyDown(KEY_UP)) shark->rectangle.y -= shark->speed;
    if(IsKeyDown(KEY_DOWN)) shark->rectangle.y += shark->speed;
}

void upgradeShark(Shark *shark){
    shark->rectangle.height *= 1.05;
    shark->rectangle.width *= 1.05;
}

void drawShark(Shark *shark){
    DrawRectangleRec(shark->rectangle, BLUE);
}