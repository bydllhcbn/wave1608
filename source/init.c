#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "init.h"
#include "functions.h"
#include "game.h"

//initial values first
int bulletAI = 1;
int enemyAI = 1;
int animationAI = 1;
const int WIDTH = 800;
const int HEIGHT = 600;
int keys[] = {0, 0, 0, 0, 0};
int enemyCount = 0;
int bulletCount = 0;
int waitFor = 0;
int totalScore = 0;
int maxBullets = 6;
bool autoPilotOn = 0;
//INITIALIZE A FRESH GAME
int initialize(){

    //Handle Sounds
    if(isSoundsOpen){
        al_reserve_samples(100);
    }else{
        al_reserve_samples(isMusicsOpen);
    }
    playerHealth = 100;
    playerLives = 3;
    totalScore = 0;

	bulletHead = malloc(sizeof(Bullet));
    bulletHead->id = 0;
    bulletHead->x = -1608.0;
    bulletHead->y = -1608.0;
    bulletHead->velX = 0.0;
    bulletHead->velY = 0.0;
    bulletHead->image = fireImage;
    bulletHead->next = NULL;

    animationHead = malloc(sizeof(Animation));
    animationHead->id = 0;
    animationHead->x = -1608.0;
    animationHead->y = -1608.0;
    animationHead->sheet = explosion;
    animationHead->next = NULL;

    enemyHead = malloc(sizeof(Enemy));
    enemyHead->id = 0;
    enemyHead->x = +1608.0;
    enemyHead->y = +1608.0;
    enemyHead->velX = 0.0;
    enemyHead->velY = 0.0;
    enemyHead->followPath = false;
    enemyHead->followPlayer = false;
    enemyHead->fireSpeed = 0;
    enemyHead->health = 16008+1;
    enemyHead->image = controllableImage;
    enemyHead->bulletImage = fireImage;
    enemyHead->next = NULL;



    player.bulletImage = fireImage;
    player.health = 100;
    player.speed = 5;
    player.damage = 10;
    player.x = WIDTH/2-player.w/2;
    player.y = (HEIGHT/8)*7;



    return 0;
}
