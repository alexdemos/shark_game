#ifndef CAMERA_H_
#define CAMERA_H_
#include "raylib.h"
#include "shark.h"

void initCamera(Camera2D *camera, Shark *shark);
void updateCamera(Camera2D *camera, Shark *shark, int SCREEN_BUFFER);

#endif