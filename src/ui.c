#include "ui.h"
#include "raylib.h"

void drawHealthBar(int health){
    int i;
    int screenWidth = GetScreenWidth();
    for (i = 1; i <= health; i++){
        DrawCircle(screenWidth - (30*i), 10, 10, RED);
    }
}