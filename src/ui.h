#ifndef UI_H_
#define UI_H_
#include "shark.h"

void drawUI(Shark *shark);
void drawHealthBar(float health, int width, int height);
void drawXpBar(int level, float xp, int width, int height);

#endif