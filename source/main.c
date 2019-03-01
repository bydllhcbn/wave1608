#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "init.h"
#include "functions.h"
#include "game.h"
#include "system.h"
#include "menu.h"
//==============================================================00
//==========================Wave: 1608==========================00
//=====================================(ScRiPeR)================00
//=======================(20.08.2017)===========================00
int main(int argc, char **argv){
    int   ScRiPeR = 2;//0 = SHUTDOWN; 1=GAME; 2=MAIN MANU; 3=SETTINGS; 4=GAME OVER; 5=HIGH SCORES; 6=SHIP SELECT;
    initSystem(0);
    while(ScRiPeR){
        if(ScRiPeR == 1) ScRiPeR = startGame();
        if(ScRiPeR == 2) ScRiPeR = mainMenu();
        if(ScRiPeR == 3) ScRiPeR = settings();
        if(ScRiPeR == 4) ScRiPeR = gameOver();
        if(ScRiPeR == 5) ScRiPeR = highScores();
        if(ScRiPeR == 6) ScRiPeR = shipSelect();
    }
    shutdownSystem();
	return 0;
}
