#include "shark.h"
#include "enemies.h"
#include "collisions.h"

#include "raylib.h"
#include "raymath.h"
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
        if(checkCollision(shark, enemies[i]->rectangle)){
            processCollision(shark, enemies[i], world);
        } 
    }
}

bool checkCollision(Shark *shark, Rectangle enemy){
    Vector2 shark_center = (Vector2){shark->rectangle.x, shark->rectangle.y};
    Vector2 shark_top_left;
    Vector2 shark_top_right;
    Vector2 shark_bottom_right;
    Vector2 shark_bottom_left;

    if ((shark -> direction == 1 && shark -> rotation != 0) || 
        (shark -> direction == 0 && shark -> rotation == 0)) {
        shark_top_left = (Vector2){shark->rectangle.x - shark->rectangle.width/2,
                        shark->rectangle.y - shark->rectangle.height/2} ;
        shark_top_right = (Vector2){shark->rectangle.x + shark->rectangle.width/2 ,
                      shark->rectangle.y - shark->rectangle.height/2};
        shark_bottom_right = (Vector2){shark->rectangle.x + shark->rectangle.width/2,
                      shark->rectangle.y + shark->rectangle.height/2};
        shark_bottom_left = (Vector2){shark->rectangle.x - shark->rectangle.width/2,
                      shark->rectangle.y + shark->rectangle.height/2};
    } else {
        shark_top_left = (Vector2){shark->rectangle.x + shark->rectangle.width/2,
                        shark->rectangle.y + shark->rectangle.height/2} ;
        shark_top_right = (Vector2){shark->rectangle.x - shark->rectangle.width/2 ,
                      shark->rectangle.y + shark->rectangle.height/2};
        shark_bottom_right = (Vector2){shark->rectangle.x - shark->rectangle.width/2,
                      shark->rectangle.y - shark->rectangle.height/2};
        shark_bottom_left = (Vector2){shark->rectangle.x + shark->rectangle.width/2,
                      shark->rectangle.y - shark->rectangle.height/2};
    }
    
    Vector2 enemyCorners[4] = {
        (Vector2){enemy.x, enemy.y},
        (Vector2){enemy.x + enemy.width, enemy.y},
        (Vector2){enemy.x + enemy.width, enemy.y + enemy.height},
        (Vector2){enemy.x, enemy.y + enemy.height}
    };

    //rotate
    Vector2 corners[4] = {
    rotate(shark_top_left, shark_center, shark->rotation),
    rotate(shark_top_right, shark_center, shark->rotation),
    rotate(shark_bottom_right, shark_center, shark->rotation),
    rotate(shark_bottom_left, shark_center, shark->rotation)
    };

    //draw shark hitbox
    // Vector2 size = (Vector2){10,10};
    // DrawRectangleV(corners[0],size,BLACK);
    // DrawRectangleV(corners[1],size,GREEN);
    // DrawRectangleV(corners[2],size,PURPLE);
    // DrawRectangleV(corners[3],size,RED);

    Vector2 axis[2] = {
        (Vector2){(corners[2].x - corners[3].x), corners[2].y - corners[3].y}, //bottom
        (Vector2){(corners[0].x - corners[3].x), corners[0].y - corners[3].y}, //left
    };
    
    double magnitude;
    for (int i = 0; i < 2; i++) {
        magnitude = (axis[i].x * axis[i].x) + (axis[i].y * axis[i].y);
        axis[i].x /= magnitude;
        axis[i].y /= magnitude;
    }
    
    double origin[2] = {
        Vector2DotProduct(corners[3], axis[0]),
        Vector2DotProduct(corners[3], axis[1])
    };  
    
    for(int a = 0; a<2; a++){
        double p2min = Vector2DotProduct(axis[a], enemyCorners[0]);
        double p2max = p2min;
        for(int i = 1; i < 4; i++) {
            double dot = Vector2DotProduct(axis[a], enemyCorners[i]);
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

