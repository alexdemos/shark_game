#include "ui.h"
#include "raylib.h"

const int STATUS_BAR_HEIGHT = 25;
const int STATUS_BAR_WIDTH = 250;
const int STATUS_BAR_OFFSET = 25;
const int HEALTH_BAR_Y = 25;

void drawUI(Shark *shark){
    drawHealthBar(shark->health);
    drawXpBar(shark->level, shark->xp);
}

void drawHealthBar(float health){
    int x = (STATUS_BAR_OFFSET + STATUS_BAR_WIDTH);
    float healthPortion = (health/100) * STATUS_BAR_WIDTH;
    float emptyPortion = STATUS_BAR_WIDTH - healthPortion;
    float emptyX = (x - STATUS_BAR_WIDTH) + (-healthPortion + STATUS_BAR_WIDTH);
    DrawRectangle(GetScreenWidth() - x, STATUS_BAR_HEIGHT, healthPortion, STATUS_BAR_HEIGHT, RED);
    DrawRectangle(GetScreenWidth() - emptyX, STATUS_BAR_HEIGHT, emptyPortion, STATUS_BAR_HEIGHT, WHITE);
}

void drawXpBar(int level, int xp){
    int x = (STATUS_BAR_OFFSET + STATUS_BAR_WIDTH);
    int y = HEALTH_BAR_Y + (STATUS_BAR_HEIGHT * 2);
    float nextLevelXp = calculateNextLevelXp(level);
    float xpPortion = (xp / nextLevelXp) * STATUS_BAR_WIDTH;
    float emptyPortion = STATUS_BAR_WIDTH - xpPortion;
    float emptyX = (x - STATUS_BAR_WIDTH) + (STATUS_BAR_WIDTH - xpPortion);
    DrawRectangle(GetScreenWidth() - x, y, xpPortion, STATUS_BAR_HEIGHT, GREEN);
    DrawRectangle(GetScreenWidth() - emptyX, y, emptyPortion, STATUS_BAR_HEIGHT, WHITE);
}