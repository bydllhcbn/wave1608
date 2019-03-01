#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "init.h"
#include "functions.h"
#include "game.h"
#include "prefabs.h"
#include "autoPilot.h"
#include <math.h>

float dist = 0.0;
Bullet * bl = NULL;
int targetX;
int inDanger = 0;

int frontDanger(float dist){
return (dist<160 && bl->type == 1 && bl->x>(player.x-20)
        && bl->x<(player.x+player.w+20)
        && abs(bl->velX)<1.5);
}
int rightDanger(float dist){
return (dist<200 && bl->type == 1 && bl->x>(player.x+player.w) && bl->velX<0.0 );
}
int leftDanger(float dist){
return (dist<200 && bl->type == 1 && bl->x<(player.x) && bl->velX>0.0 );
}
void goLeft(){
player.x -= player.speed;
}
void goRight(){
player.x += player.speed;
}

//This is not smart enough to play all along but can be developed
void autoPilot(){
    Enemy * nearest = nearestEnemy();
    float nearestEnemyDistance;
    int iLeft = 0;
    int iRight = 0;
    int nLeft = 0;
    int nRight = 0;
    nearestEnemyDistance = distance(player.x,player.y,nearest->x,nearest->y);
    targetX = nearest->x;

    if(player.y <540 && !inDanger){
        player.y += player.speed;
    }else if(nearestEnemyDistance<100){
            if(nearest->x>player.x){
                goLeft();
            }else{
                goRight();
            }
    }else{


    Bullet * bullet = bulletHead;
    inDanger = FALSE;
    while (bullet != NULL) {
        bl = bullet;
        dist = distance(player.x,player.y,bullet->x,bullet->y);
        if(frontDanger(dist)&&player.x>(WIDTH-40)){
            iLeft = true;
            break;
        }else if(frontDanger(dist)){
            iRight = true;
            break;
        }else{
        if(rightDanger(dist) && player.x<0){
            player.y -= player.speed/2;
        }else if(rightDanger(dist)){
            //al_draw_filled_rectangle(bullet->x, bullet->y, bullet->x+bullet->width, bullet->y+bullet->height, al_map_rgba_f(.6, 0, .6, .6));
            if(dist<100){
                iLeft = 1;
                break;
            }else{
                nRight = 1;
            }
        }
            if(leftDanger(dist) && player.x>(WIDTH-40)){
                player.y -= player.speed/2;
            }else if(leftDanger(dist)){
               // al_draw_filled_rectangle(bullet->x, bullet->y, bullet->x+bullet->width, bullet->y+bullet->height, al_map_rgba_f(.6, 0, .1, .6));
                if(dist<100){
                    iRight = 1;
                    break;
                }else{
                    nLeft = 2;
                }
            }
        }
        if(dist < 180 && bullet->type == 1){
            inDanger = TRUE;
        }
        bullet = bullet->next;
    }

    if(iRight){
        goRight();
    }else if(iLeft){
        goLeft();
    }else if(nRight){
        goRight;
    }else if(nLeft){
        goLeft();
    }else if(abs(player.x-targetX) > 3){
        if(player.x>(targetX-6) && !inDanger){
            goLeft();
        }else if(player.x<(targetX-6) && !inDanger){
            goRight();
        }
    }


     }
}
