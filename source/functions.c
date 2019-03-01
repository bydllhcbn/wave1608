#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "init.h"
#include "functions.h"
#include "game.h"
#include "prefabs.h"
#include <math.h>

double distance(int x1,int y1,int x2,int y2){
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int randomNumber(int n) {
    long end = RAND_MAX/n;assert(end>0L);end *= n;int r;
    while ((r=rand())>=end);
    return r % n;
}

int randomDecision() {
  return randomNumber(2);
}


Enemy * createEnemy(float x,float y,float velX,float velY,int health,
    int fireSpeed,int damage,ALLEGRO_BITMAP *image,bool followPath,bool followPlayer) {
    Enemy * current = enemyHead;
    //Just getting around on RAM
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(Enemy));
    current->next->id = enemyAI; //A new uniqe ID
    current->next->x = x;
    current->next->y = y;
    current->next->maxY = randomNumber(HEIGHT/2-100)+50;
    current->next->velX = velX;
    current->next->velY = velY;
    current->next->followPlayer = followPlayer;
    current->next->followPath = followPath;
    if(followPath){
        if(randomDecision()){
        current->next->velX = 1 + randomDecision();
        }else{
        current->next->velX = -1 - randomDecision();
        }
    }
    current->next->w = al_get_bitmap_width(image)/4;
    current->next->h = al_get_bitmap_height(image)/4;
    current->next->health = health;
    current->next->fireSpeed = fireSpeed;
    current->next->bulletImage = NULL;
    current->next->damage = damage;
    current->next->image = image;
    current->next->next = NULL;
    enemyAI++; //It is called auto increment
    enemyCount++;
    return current->next;
}


void createBullet(float x,float y,float velX,float velY,int type,ALLEGRO_BITMAP *image,int damage) {
//printf("createBullet called\n");

    Bullet * current = bulletHead;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(Bullet));
    current->next->id = bulletAI; //A new uniqe ID
    current->next->x = x;
    current->next->y = y;
    current->next->velY = velY;
    if (type==1 && image==missileImage){
        //Determine the speed axis of the bullet
        double reachTime = distance(player.x,player.y,x,y)/abs(velY);
        current->next->velX = (player.x-x)/reachTime;
        current->next->velY = (player.y-y)/reachTime;
        //printf("%f - %f",current->next->velX,current->next->velY);
        bulletCount++;
    }


    //Determine bullet rotation once ADDED 1.57(pi/2) to fix initial rotate
    current->next->rotation = atan2(current->next->velY,current->next->velX) + 1.57;

    if (type==0) {
            current->next->velX = velX;
            current->next->rotation = 0.0;
    }

    current->next->type = type;
    current->next->damage = damage;
    current->next->width = al_get_bitmap_width(image)/4;
    current->next->height = al_get_bitmap_height(image)/4;
    current->next->image = image;
    current->next->next = NULL;
    bulletAI++; //It is called auto increment tho
}

int removeBullet(int id) {
    //printf("removeBullet called\n");

    Bullet *previous, *current;
    if (bulletHead == NULL) {
        return -1;
    }

    //We cant cut of the head
    if ((bulletHead)->id == id) {
        return -1;
    }

    previous = current = bulletHead;
    while (current) {
        if (current->id == id) {
                if (current->type==1){
                    bulletCount--;
                }

            previous->next = current->next;
            free(current);
            return id;
        }

        previous = current;

        current  = current->next;
    }
    return -1;
}


int removeEnemy(int id) {
     //   printf("removeEnemy called\n");

    Enemy *previous, *current;

    //We cant cut of the head
    if ((enemyHead)->id == id) {
        return -1;
    }
    previous = current = enemyHead;
    while (current) {
        if (current->id == id) {

            // DELETE THE OBJECT BRUTALLY
            previous->next = current->next;
            free(current);
            enemyCount--;
            //printf("Removed an enemy !\n");
            return id;
        }
        previous = current;
        current  = current->next;
    }

    return -1;
}
void createAnimation(float x,float y,int maxFrame,int frameDelay,int frameWidth,int frameHeight,ALLEGRO_BITMAP *sheet) {
    Animation * current = animationHead;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(Animation));
    current->next->id = animationAI; //A new uniqe ID
    current->next->x = x;
    current->next->y = y;
    current->next->maxFrame = maxFrame;
    current->next->frameDelay = frameDelay;
    current->next->frameWidth = frameWidth;
    current->next->frameHeight = frameHeight;
    current->next->curFrame = 0;
    current->next->frameCount = 0;
    current->next->looped = 0;
    current->next->sheet = sheet;
    current->next->next = NULL;
    animationAI++; //It is called auto increment tho
}

int removeAnimation(int id) {
    Animation *previous, *current, *next;
    if (animationHead == NULL) {
        return -1;
    }
    //We cant cut of the head
    if ((animationHead)->id == id) {
        return -1;
    }
    previous = current = animationHead;
    while (current) {

        if (current->id == id) {
            previous->next = current->next;
            free(current);
            return id;
        }
        previous = current;
        current  = current->next;
    }
    return -1;
}

void removeAll(){
    //LETS FREE OUR MEMORY
    Bullet *current = bulletHead;
    Bullet *next;
    while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }
    bulletHead = NULL;

    Enemy *current2 = enemyHead;
    Enemy *next2;
    while (current2 != NULL)
    {
       next2 = current2->next;
       free(current2);
       current2 = next2;
    }
    enemyHead = NULL;
}


void createEnemiesByTime(){
    int aNumber = 0;
    int seconds = TIME/60;
    if(seconds<10){
        if(enemyCount<6  && seconds%3){
                maxBullets = 6;
                createStaticEnemy1(randomNumber(WIDTH-50)+5,-50);

        }
    }else if(seconds<20){
        if(enemyCount<7 && seconds%2){
                maxBullets = 5;
                if(randomNumber(2)){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-90);
                }else{
                    createStaticEnemy1(randomNumber(WIDTH-50)+5,-50);
                }

        }

    }else if(seconds<40){

        if(enemyCount<8 && seconds%2){
                maxBullets = 6;
                aNumber = randomNumber(3);
               if(aNumber){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(!aNumber){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else{
                    createStaticEnemy1(randomNumber(WIDTH-50)+5,-50);
                }

        }


    }else if(seconds<80){

        maxBullets = 7;
        if(enemyCount<11 && seconds%2){
                aNumber = randomNumber(4);
               if(aNumber == 3){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 2){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 1){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else{
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }
        }


    }else if(seconds<120){

        maxBullets = 7;
        if(enemyCount<11 && seconds%2){

                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);

        }


    }else if(seconds<180){
        maxBullets = 16;
        if(enemyCount<12 && seconds%2){
                aNumber = randomNumber(5);
               if(aNumber == 4){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 3){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 2){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 1){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 0){
                    createDynamicEnemy2(randomNumber(WIDTH-50)+5,-50);
                }
        }

    }else if(seconds<240){
        maxBullets = 18;
        if(enemyCount<15 && seconds%2){
                aNumber = randomNumber(5);
               if(aNumber == 4){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 3){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 2){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 1){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 0){
                    createDynamicEnemy2(randomNumber(WIDTH-50)+5,-50);
                }
        }

    }else if(seconds<360){
        maxBullets = 20;
        if(enemyCount<17 && seconds%2){
                aNumber = randomNumber(5);
               if(aNumber == 4){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 3){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 2){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 1){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 0){
                    createDynamicEnemy2(randomNumber(WIDTH-50)+5,-50);
                }
        }

    }else{

         if(enemyCount<20 && seconds%5){
                maxBullets = 25;
                aNumber = randomNumber(5);
               if(aNumber == 4){
                     createStaticEnemy3(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 3){
                    createStaticEnemy2(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 2){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 1){
                    createDynamicEnemy1(randomNumber(WIDTH-50)+5,-50);
                }else if(aNumber == 0){
                    createDynamicEnemy2(randomNumber(WIDTH-50)+5,-50);
                }
        }

    }

}


Enemy * nearestEnemy(){
    //LOOP THROUGH ALL ENEMIES
    Enemy * enemy = enemyHead;
    Enemy * nearest = enemyHead;
    float minDist = 16008;
    float dist;
    while (enemy != NULL) {
         dist = distance(player.x,player.y,enemy->x,enemy->y);
        if (dist<minDist) {
            minDist=dist;
            nearest = enemy;
        }
        enemy = enemy->next;
    }
    return nearest;
}

Enemy * weakestEnemy(){
    //LOOP THROUGH ALL ENEMIES
    Enemy * enemy = enemyHead;
    Enemy * weakest = enemyHead;
    int minH = 16008;
    int h;
    while (enemy != NULL) {
         h = enemy->health;
        if (h<minH) {
            minH=h;
            weakest = enemy;
        }
        enemy = enemy->next;
    }
    return weakest;
}
