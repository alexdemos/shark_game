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
        //if(CheckCollisionRecs(collider, enemies[i]->rectangle)){
        if(checkCollision(shark, enemies[i]->rectangle)){
            processCollision(shark, enemies[i], world);
        } 
    }
    //checkCollision(shark, enemies[0]->rectangle);
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
    Vector2 enemyCorners[4] = {
        (Vector2){enemy.x - enemy.width/2, enemy.y - enemy.height/2},
        (Vector2){enemy.x + enemy.width/2, enemy.y - enemy.height/2},
        (Vector2){enemy.x + enemy.width/2, enemy.y + enemy.height/2},
        (Vector2){enemy.x - enemy.width/2, enemy.y + enemy.height/2}
    };
    //rotate
    Vector2 corners[4] = {
    rotate(shark_top_left, shark_center, shark->rotation),
    rotate(shark_top_right, shark_center, shark->rotation),
    rotate(shark_bottom_right, shark_center, shark->rotation),
    rotate(shark_bottom_left, shark_center, shark->rotation)
    };

    Vector2 axis[2] = {
        (Vector2){(corners[2].y - corners[3].y), corners[2].x - corners[3].x},
        (Vector2){(corners[0].y - corners[3].y), corners[0].x - corners[3].x}
    };

    double magnitude = sqrt(pow(axis[0].x,2) + pow(axis[0].y,2));
    if (magnitude != 0){
        axis[0].x /= magnitude;
        axis[0].y /= magnitude;
    }
    magnitude = sqrt(pow(axis[1].x,2) + pow(axis[1].y,2));
    if (magnitude != 0){
        axis[1].x /= magnitude;
        axis[1].y /= magnitude;
    }

    double origin[2] = {
        dotProduct(corners[3], axis[0]),
        dotProduct(corners[3], axis[1])
    };  
    
    for(int a = 0; a<2; a++){
        double p2min = dotProduct(axis[a], enemyCorners[0]);
        double p2max = p2min;
        for(int i = 1; i < 4; i++) {
            double dot = dotProduct(axis[a], enemyCorners[i]);
            if (dot > p2max){
                p2max = dot;
            }
            if (dot < p2min){
                p2min = dot;
            }
        }

        if ((p2min > 1 + origin[a]) || (p2max < origin[a])){
            return false;
        }
    }
    return true;

    //Vector2 size = (Vector2){4,4};
    // DrawRectangleV(r_top_right,size,BLACK);
    // DrawRectangleV(r_top_left,size,BLACK);
    // DrawRectangleV(r_bottom_left,size,BLACK);
    // DrawRectangleV(r_bottom_right,size,BLACK);
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

double dotProduct(Vector2 point1, Vector2 point2){
    return (point1.x * point2.x) + (point1.y * point2.y);
}
