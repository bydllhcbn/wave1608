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
#include "autoPilot.h"


float missileX = -20.0;
float missileY = -20.0;
bool missileExists = FALSE;
Enemy * missileTarget;
float missileRotation = 0;
float weakestRotation = 0;
Enemy * weakest;
double dista;
int cooldown = 0;

void handleGUI(){

    al_draw_textf(font22,al_map_rgb(255, 0, 0),5,20,0,"Score : %d",totalScore+TIME/10);

    if(playerLives >= 3) al_draw_scaled_rotated_bitmap(player.image,0, 0,90, 50, 0.2, 0.2,0, 0);
    if(playerLives >= 2) al_draw_scaled_rotated_bitmap(player.image,0, 0,50, 50, 0.2, 0.2,0, 0);
    if(playerLives >= 1) al_draw_scaled_rotated_bitmap(player.image,0, 0,10, 50, 0.2, 0.2,0, 0);
    if(autoPilotOn){
        al_draw_text(font13,al_map_rgb(255, 255, 255),5,HEIGHT-20,0,"Autopilot: ON [Space to toggle]");
    }else{
        al_draw_text(font13,al_map_rgb(255, 255, 255),5,HEIGHT-20
                     ,0,"Autopilot: OFF [Space to toggle]");
    }

}


void handlePlayer(){

    //Lazer ships fire double bullet others one
        if(player.type == laserShip){
              if((TIME % 30) == 0){
                    createBullet(player.x+6,player.y-12,0,-5,0,player.bulletImage,50);
                    createBullet(player.x+25,player.y-12,0,-5,0,player.bulletImage,50);
                    al_play_sample(gunSound1, 0.6, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            }
        }else{
            if((TIME % 15) == 0){
                    createBullet(player.x+8,player.y-12,0,-5,0,player.bulletImage,50);
                    al_play_sample(gunSound1, 0.6, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            }
        }


    if(player.type == laserShip && enemyCount){
        if(TIME%300 == 0){
            al_play_sample(laserSound, 1, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }
        if(TIME%300 == 5){
            al_play_sample(laserSound, 1, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }
        if(TIME%300 < 40 ){
            al_draw_scaled_rotated_bitmap(laserImage,100, 0,player.x+25, player.y-810, 0.1, 0.8, 0, 0);
        }

    }

    if(player.type == lightningShip){
        if(TIME%240 == 239  && enemyCount){
            weakest = weakestEnemy();
            dista = distance(player.x,player.y,weakest->x,weakest->y);
            createAnimation(weakest->x-(45-weakest->w)/2,weakest->y-(45-weakest->h)/2,11,5,90,90,explosion);
            al_play_sample(lightningSound, 1, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            al_play_sample(explosionSound1, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            weakestRotation = atan2(player.y-weakest->y,player.x-weakest->x)+3.14;
            removeEnemy(weakest->id);
        }

        if(TIME%240 < 9 && enemyCount){
            al_draw_scaled_rotated_bitmap(lightningImage,17, 235,player.x+10, player.y+10, 0.3*(dista/614.0), 0.2, weakestRotation, 0);

        }

    }


    if(player.type == missileShip){
        if(TIME%200==199  && enemyCount && !waitFor){
            al_play_sample(missileSound, 2, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

            missileX = player.x;
            missileY = player.y;
            missileTarget = nearestEnemy();
            missileExists = TRUE;
            missileRotation = 0;

        }

        //If missile is fired redirect it to nearest enemy
        if(missileExists && enemyCount){
            al_draw_scaled_rotated_bitmap(missileImage,25*2, 29*2,missileX+25/2, missileY+28/2, 0.3, 0.3, missileRotation, 0);
            //al_draw_filled_rectangle(missileX,missileY, missileX+29, missileY+29, al_map_rgba_f(.6, 0, .6, .6));

            int timex = abs(missileTarget->y - missileY)/3;
            float velX = (missileTarget->x-missileX)/timex;
            if(velX<-20){
                velX = -20;
            }
            if(velX>20){
                velX = 20;
            }
            missileRotation = atan2(-5,velX) + 1.57;

            missileX = missileX + velX;
            missileY = missileY - 7;

        }

    }


    //MOVEMENT
    if(keys[UP] && player.y>0)                       player.y -= player.speed;
    else if(keys[DOWN] && player.y<HEIGHT-player.h)  player.y += player.speed;
    if(keys[LEFT] && player.x>0)                     player.x -= player.speed;
    else if(keys[RIGHT] && player.x<WIDTH-player.w)  player.x += player.speed;


    //DRAW CONTROLLABLE AIRCRAFT
    if(cooldown>0){
        if(TIME%20 < 10){
                al_draw_scaled_rotated_bitmap(player.image,0, 0,player.x, player.y, 0.25, 0.25,0, 0);
        }
        cooldown--;
    }else{
            al_draw_scaled_rotated_bitmap(player.image,0, 0,player.x, player.y, 0.25, 0.25,0, 0);
    }

    if(playerLives == 0){
        isGameOver = true;
        waitFor = 0;
        cooldown = 0;
    }
    if(playerHealth <= 0){
        playerLives--;
        createAnimation(player.x-(45-player.w)/2,player.y-(45-player.h)/2,11,5,90,90,explosion);
        waitFor = 120;
        cooldown = 200;
        player.x = WIDTH/2-player.w/2;
        player.y = (HEIGHT/8)*7;
        playerHealth = 100;

        //For training auto pilot stop time and check
        //al_stop_timer(timer);
    }
}

void handleBullets(){
  //Draw All Bullets
    Bullet * bullet = bulletHead;
    Bullet * bulletNext = bulletHead;
    while (bullet != NULL) {
        bulletNext = bullet->next;

        //Dont touch the head
        if(bullet->id){

        //DRAW THE BULLET
        al_draw_scaled_rotated_bitmap(bullet->image,bullet->width*2, bullet->height*2,bullet->x+bullet->width/2, bullet->y+bullet->height/2, 0.25, 0.25,bullet->rotation, 0);
        //al_draw_filled_rectangle(bullet->x, bullet->y, bullet->x+bullet->width, bullet->y+bullet->height, al_map_rgba_f(.6, 0, .6, .6));

        bullet->x = bullet->x + bullet->velX;
        bullet->y = bullet->y + bullet->velY;
//==============================================================00
//=============BOUNDING BOX COLLISION DETECTION ================00
//==============================================================00
        //WHEN THE PLAYER GOT SHOT
        if(bullet->type == 1){
            if( player.x + player.w > bullet->x&&
				player.x< bullet->x + bullet->width &&
				player.y + player.h > bullet->y &&
				player.y < bullet->y + bullet->height)
			{
				//printf("Player got shot !\n");
				if(cooldown==0 && waitFor==0){
                createAnimation(bullet->x-10,bullet->y+5,10,1,64,64,bulletExplosion);
				playerHealth -= bullet->damage;
				removeBullet(bullet->id);
				}

			}
        //WHEN AN ENEMY GOT SHOT
        }else if(bullet->type == 0){
                Enemy * enemy = enemyHead;
                while (enemy != NULL) {

                        if( enemy->x + enemy->w  > bullet->x&&
                            enemy->x             < bullet->x + bullet->width &&
                            enemy->y + enemy->h  > bullet->y &&
                            enemy->y             < bullet->y + bullet->height)
                        {
                        //    printf("An enemy got shot !\n");
                        al_play_sample(explosionSound2, 1, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                            createAnimation(bullet->x-10,bullet->y-5,10,1,64,64,bulletExplosion);
                            enemy->health -= bullet->damage;
                            removeBullet(bullet->id);
                            break;

                        }

                        enemy = enemy->next;
                }

        }
            //When bullet gets out of screen remove
            if(bullet->y<0 || bullet->y>HEIGHT){
                removeBullet(bullet->id);
            }


        }


        bullet = bulletNext;
    }

}


void handleEnemies(){

    //LOOP THROUGH ALL ENEMIES
    Enemy * enemy = enemyHead;
    Enemy * enemyNext = enemyHead;
    while (enemy != NULL) {
            enemyNext = enemy->next;
        if(enemy->id){


        //DRAW THE ENEMY
        al_draw_scaled_rotated_bitmap(enemy->image,0, 0,enemy->x, enemy->y, 0.25, 0.25,0, 0);
        //al_draw_filled_rectangle(enemy->x, enemy->y, enemy->x+enemy->w, enemy->y+enemy->h, al_map_rgba_f(.6, 0, .6, .6));

        //SPEED THE ENEMY
        if(enemy->followPath){
            if(enemy->x<0 || enemy->x>(WIDTH-50)){
                enemy->velX = (-1)*enemy->velX;
            }
            if(enemy->y > enemy->maxY){
                enemy->velY = (-1)*enemy->velY;
            }
            if(enemy->y < 0 && enemy->velY<0){
                enemy->velY = (-1)*enemy->velY;
            }
        }
        if(enemy->followPlayer && !waitFor){

            int timex = abs(player.y - enemy->y)/enemy->velY;

            enemy->velX = (player.x-enemy->x)/timex;
            if(enemy->velX>2){
                enemy->velX = 2;
            }
            if(enemy->velX<-2){
                enemy->velX = -2;
            }
        }

            if(enemy->y<enemy->maxY || enemy->followPlayer || enemy->followPath){
                enemy->y = enemy->y + enemy->velY;
            }

            enemy->x = enemy->x + enemy->velX;

        //REMOVE WHEN GETS OUT OF SCREEN
        if(enemy->y>HEIGHT){
            //****************************
            //ADDED continue to fix the bug WE CANT REACH ENEMY AFTER REMOVING
            removeEnemy(enemy->id);
            enemy = enemyNext;
            continue;
        }

    //When enemy hits the player
        if( player.x + player.w > enemy->x&&
				player.x< enemy->x + enemy->w &&
				player.y + player.h > enemy->y &&
				player.y < enemy->y + enemy->h)
        {
                if(cooldown==0 && waitFor==0){
                    createAnimation(enemy->x-(45-enemy->w)/2,enemy->y-(45-enemy->h)/2,11,5,90,90,explosion);
                    playerHealth = 0;
                    al_play_sample(explosionSound1, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    removeEnemy(enemy->id);
                    enemy = enemyNext;
                    continue;
                }

        }

        //When enemy hits the missile
        if(player.type == missileShip){
            if( missileX + 32 > enemy->x&&
				missileX - 15 < enemy->x + enemy->w &&
				missileY + 32 > enemy->y &&
				missileY -5 < enemy->y + enemy->h)
            {
                    missileExists = FALSE;
                    missileX = -20.0;
                    missileY = -20.0;
                    al_play_sample(explosionSound1, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                    createAnimation(enemy->x-(45-enemy->w)/2,enemy->y-(45-enemy->h)/2,11,5,90,90,explosion);
                    totalScore += 50;
                    removeEnemy(enemy->id);
                    enemy = enemyNext;
                    continue;
			}


        }

        //When enemy hits the laser
        if(player.type == laserShip){

            if(TIME%300 < 40){
                 if( player.x + 25     > enemy->x&&
                    player.x           < enemy->x + enemy->w &&
                    player.y + 29      > enemy->y &&
                    player.y -1000          < enemy->y + enemy->h)
                {
                    al_play_sample(explosionSound1, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                    createAnimation(enemy->x-(45-enemy->w)/2,enemy->y-(45-enemy->h)/2,11,5,90,90,explosion);
                    removeEnemy(enemy->id);
                    enemy = enemyNext;
                    totalScore += 50;
                    continue;
                }
            }

        }


        //CREATE BULLETS PERIODICALLY BY FIRESPEED
        if(enemy->fireSpeed != 0){
            if((TIME % (480/enemy->fireSpeed)) == 0){

                if(bulletCount<maxBullets && randomDecision() && enemy->y<player.y && !waitFor) {
                        createBullet(enemy->x+enemy->w/2,enemy->y+enemy->h/2,0,4,1,enemy->bulletImage,enemy->damage);}
            }
        }
        if(enemy->health <= 0){
                    al_play_sample(explosionSound1, 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    createAnimation(enemy->x-(45-enemy->w)/2,enemy->y-(45-enemy->h)/2,11,5,90,90,explosion);
                    removeEnemy(enemy->id);
                    enemy = enemyNext;
                    totalScore += 50;
                    continue;
        }



        }
        enemy = enemy->next;
    }
}







void handleAnimations(){
    //LOOP THROUGH ALL ANIMATIONS
    Animation * a = animationHead;
    Animation * aNext = animationHead;
    while (a != NULL) {
        aNext = a->next;
        if(a->id){
        al_draw_tinted_scaled_rotated_bitmap_region(a->sheet, a->curFrame * a->frameWidth, 0, a->frameWidth, a->frameHeight,al_map_rgb(255, 255, 255),
                                                            0,0,a->x,a->y,0.6,0.6,0,0);
            // al_draw_bitmap_region(a->sheet, a->curFrame * a->frameWidth, 0, a->frameWidth, a->frameHeight, a->x, a->y, 0,0);
        if(++a->frameCount >= a->frameDelay)
			{
				if(++(a->curFrame) >= a->maxFrame){
                    a->curFrame = 0;
                    if(!a->looped) {
                            removeAnimation(a->id);
                            a = aNext;
                            continue;
                    }
				}
				a->frameCount = 0;
			}
        }
        a = aNext;
    }
}



float stary = 0;
void handleBackground(){
    al_draw_scaled_rotated_bitmap(spaceBackground,0, 0,0, 0, 0.5, 0.5,0, 0);
    al_draw_scaled_rotated_bitmap(spaceBackground,0, 0,512, 512, 0.5, 0.5,0, 0);
    al_draw_scaled_rotated_bitmap(spaceBackground,0, 0,512, 0, 0.5, 0.5,0, 0);
    al_draw_scaled_rotated_bitmap(spaceBackground,0, 0,0, 512, 0.5, 0.5,0, 0);
    al_draw_scaled_rotated_bitmap(spaceStars,0, 0,0, stary-1024, 1, 1,0, 0);
    al_draw_scaled_rotated_bitmap(spaceStars,0, 0,0, stary, 1, 1,0, 0);
    al_draw_scaled_rotated_bitmap(spaceStars,0, 0,0, stary+1024, 1, 1,0, 0);

    if(stary>1024){
        stary = 0;
    }
    stary += 0.2;
}



//Main update function (like unity :)
void update(){
    //This is so long so I divided into functions
    if(isBackgroundOpen){
        handleBackground();
    }
    if(!waitFor){
        handlePlayer();
    }else{
        waitFor--;
    }
    if(autoPilotOn && !waitFor){
        autoPilot();
    }
    handleBullets();
    handleEnemies();
    handleAnimations();
    handleGUI();

    //this function is in the functions.c
    createEnemiesByTime();
}






