#include "shark.h"
#include "enemies.h"
#include "collisions.h"

#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

void processCollision(Shark *shark, Enemy *enemy, World *world){
    if (shark->rectangle.height > enemy->rectangle.height){
        upgradeShark(shark, enemy->xp, enemy->healthGiven);
        recycleEnemy(enemy, world);
    } else {
        upgradeShark(shark, 0, enemy->damage);
        pauseEnemy(enemy);
    }
}

void handleCollisions(Shark *shark, Enemy **enemies, int enemyAmount, World *world){
    int i;
    Rectangle collider = (Rectangle){shark->rectangle.x-shark->rectangle.width/2,
                                shark->rectangle.y-shark->rectangle.height/2,
                                shark->rectangle.width,
                                shark->rectangle.height};
    for(i=0; i < enemyAmount; i++){
        if(CheckCollisionRecs(collider, enemies[i]->rectangle)){
            processCollision(shark, enemies[i], world);
        } 
    }
    checkCollision(shark, enemies[0]->rectangle);
}

bool checkCollision(Shark *shark, Rectangle enemy){
    Vector2 shark_center = (Vector2){shark->rectangle.x, shark->rectangle.y};
    Vector2 shark_top_left = (Vector2){shark->rectangle.x -shark->rectangle.width/2,
                      shark->rectangle.y - shark->rectangle.height/2};
    Vector2 shark_top_right = (Vector2){shark->rectangle.x + shark->rectangle.width/2,
                      shark->rectangle.y - shark->rectangle.height/2};
    Vector2 shark_bottom_right = (Vector2){shark->rectangle.x + shark->rectangle.width/2,
                      shark->rectangle.y + shark->rectangle.height/2};
    Vector2 shark_bottom_left = (Vector2){shark->rectangle.x - shark->rectangle.width/2,
                      shark->rectangle.y + shark->rectangle.height/2};
    //rotate
    Vector2 r_top_left = rotate(shark_top_left, shark_center, shark->rotation);
    Vector2 r_top_right = rotate(shark_top_right, shark_center, shark->rotation);
    Vector2 r_bottom_left = rotate(shark_bottom_left, shark_center, shark->rotation);
    Vector2 r_bottom_right = rotate(shark_bottom_right, shark_center, shark->rotation);
    Vector2 size = (Vector2){4,4};
    DrawRectangleV(r_top_left,size,BLACK);
    DrawRectangleV(r_top_right,size,BLACK);
    DrawRectangleV(r_bottom_left,size,BLACK);
    DrawRectangleV(r_bottom_right,size,BLACK);
    //make a general check to see if they are close enough
    //go through each side for both
    //project points onto perpendicular axis for a given side
    //if intersecting, keep checking, else no collison
    return true;
}

Vector2 rotate(Vector2 point, Vector2 origin, double angle){
    if (angle != 0){
        double angle_radians = angle * (PI/180);
        double new_x = ((point.x-origin.x) * cos(angle_radians)) - 
                        ((origin.y-point.y) * sin(angle_radians)) + origin.x;
        double new_y = origin.y - ((origin.y-point.y) * cos(angle_radians)) - 
                        ((point.x-origin.x) * sin(angle_radians));
        return (Vector2){new_x, new_y};
    } else{
        return point;
    }
}
