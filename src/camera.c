#include "camera.h"
#include "raylib.h"

const int SCREEN_BUFFER = 200;

void initCamera(Camera2D *camera, Shark *shark){
    camera->target = (Vector2){ shark->rectangle.x + (shark->rectangle.width / 2), 
                        shark->rectangle.y + (shark->rectangle.height / 2)};
    camera->offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera->zoom = 1.0f;
}

void updateCamera(Camera2D *camera, Shark *shark){
    float x = shark->rectangle.x + (shark->rectangle.width / 2);
    float y = shark->rectangle.y + (shark->rectangle.height / 2);
    float cameraY = camera->target.y;
    float cameraX = camera->target.x;
    Vector2 position = (Vector2){x,y};
    Vector2 screenPosition = GetWorldToScreen2D(position, *camera);  
    if (screenPosition.y < SCREEN_BUFFER){
        cameraY -= shark->speed;
    } else if (screenPosition.y > GetScreenHeight() - SCREEN_BUFFER){
        cameraY += shark->speed;
    }
    if (screenPosition.x < SCREEN_BUFFER){
        cameraX -= shark->speed;
    } else if (screenPosition.x > GetScreenWidth() - SCREEN_BUFFER){
        cameraX +=  shark->speed;
    }
    camera->target = (Vector2){cameraX, cameraY};
}