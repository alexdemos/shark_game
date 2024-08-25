#include "ui.h"
#include "shark.h"
#include "raylib.h"

void drawUI(Shark *shark){
    int width = 200;
    int height = 20;
    drawHealthBar(shark->health, width, height);
    drawXpBar(shark->level, shark->xp, width, height);
}

void drawHealthBar(float health, int width, int height){
    float healthPortion = (health/100) * width;
    float emptyPortion = width - healthPortion;
    float emptyX = 25 + (-healthPortion + width);
    DrawRectangle(GetScreenWidth() - 225, 20, healthPortion, height, RED);
    DrawRectangle(GetScreenWidth() - emptyX, 20, emptyPortion,height, WHITE);
}

void drawXpBar(int level, float xp, int width, int height){
    int nextLevelXp = level * 100;
    float xpPortion = (xp / nextLevelXp) * width;
    float emptyPortion = width - xpPortion;
    float emptyX = 25 + (-xpPortion + width);
    DrawRectangle(GetScreenWidth() - 225, 60, xpPortion, height, GREEN);
    DrawRectangle(GetScreenWidth() - emptyX, 60, emptyPortion, height, WHITE);
}