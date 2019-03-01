#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "init.h"
#include "functions.h"
#include "game.h"
#include "prefabs.h"
/*  ENEMY STRUCT HELPER
"
	bool followPlayer;
    bool followPath;
    ALLEGRO_BITMAP *bulletImage;

	x   y   velX    velY    w   h   health  fireSpeed   damage  image
*/


//Enemies as defined in the PDF
void createStaticEnemy1(int x,int y){
Enemy * createdEnemy =
createEnemy(x,y,0,2,100,0,0,enemy1Image,FALSE,FALSE);
createdEnemy->bulletImage = fireImage;
}


void createStaticEnemy2(int x,int y){
Enemy * createdEnemy =
createEnemy(x,y,0,1.2,200,4,50,enemy2Image,FALSE,FALSE);
createdEnemy->bulletImage = fireImage;
}


void createStaticEnemy3(int x,int y){
Enemy * createdEnemy =
createEnemy(x,y,0,1,250,1,100,enemy3Image,FALSE,FALSE);
createdEnemy->bulletImage = missileImage;
}


void createDynamicEnemy1(int x,int y){
Enemy * createdEnemy =
createEnemy(x,y,0,1.5,50,4,50,enemy4Image,TRUE,FALSE);
createdEnemy->bulletImage = fireImage;
}


void createDynamicEnemy2(int x,int y){
Enemy * createdEnemy =
createEnemy(x,y,0,2,250,2,50,enemy5Image,FALSE,TRUE);
createdEnemy->bulletImage = fireImage;
}
