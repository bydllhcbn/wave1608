#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "init.h"
#include "system.h"
#include "menu.h"
#include<stdio.h>


int mainMenu(){
	al_reserve_samples(isMusicsOpen);
    al_play_sample(menuMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    bool done = false;
    bool pressed = false;
    int someInt = 0;
    int selected = 0;

	//==============================================
    //MAIN GAME LOOP
    //==============================================
    ALLEGRO_EVENT ev;
	while(!done){

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
                if(!pressed){

		case ALLEGRO_KEY_LEFT:      pressed=true; keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     pressed=true; keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        pressed=true; keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      pressed=true; keys[DOWN] = true; break;
		case ALLEGRO_KEY_SPACE:     pressed=true; keys[SPACE] = true; break;
		case ALLEGRO_KEY_ENTER:     pressed=true; keys[SPACE] = true; break;

                }
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {

        case ALLEGRO_KEY_LEFT:       keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT:      keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP:         keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN:       keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE:      keys[SPACE] = false;  break;
        case ALLEGRO_KEY_ENTER:      keys[SPACE] = false;  break;
        pressed = false;
        } }
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(al_is_event_queue_empty(event_queue)){
            if(keys[DOWN]){
                if(selected == 3) selected=0; else selected++;
            }else if(keys[UP]){
                if(selected == 0) selected=3; else selected--;
            }

            if(keys[SPACE]){
                done = true;
            }
            al_draw_text(font13, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT-40, ALLEGRO_ALIGN_CENTRE, "Ubeydullah COBAN  - 161044008");
            al_draw_text(font13, al_map_rgb(255, 255, 255), WIDTH / 2-25, HEIGHT-38, ALLEGRO_ALIGN_CENTRE,         ".");
            al_draw_text(font13, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT-20, ALLEGRO_ALIGN_CENTRE,    "Summer HomeWork");
            al_draw_scaled_rotated_bitmap(logo,0, 0,WIDTH/2-180, 10, 1, 1,0, 0);
             switch(selected){
        case 0:
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "START GAME");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-70, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-10, ALLEGRO_ALIGN_CENTRE, "EXIT");
                   break;
        case 1:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "START GAME");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-70, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-10, ALLEGRO_ALIGN_CENTRE, "EXIT");
                   break;
        case 2:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "START GAME");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-70, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-10, ALLEGRO_ALIGN_CENTRE, "EXIT");
                   break;
        case 3:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "START GAME");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-70, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-10, ALLEGRO_ALIGN_CENTRE, "EXIT");
                   break;
            }

            keys[LEFT] = false;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
            keys[SPACE] = false;

			al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
		}

		al_wait_for_event(event_queue, &ev);


	}
if(selected == 3){
    return 0;
}
if(selected == 2){
    return 3;
}
if(selected == 0){
    return 6;
}
if(selected == 1){
    return 5;
}
}

int highScores(){

  bool done = false;
    bool pressed = false;
    int someInt = 0;
    int selected = 1;
    int scores[10] = {0,0,0,0,0,0,0,0,0,0};

        int i,k;
		FILE *ptr_myfile;
        //READ HIGH SCORES FILE
		ptr_myfile=fopen("data.bin","rb");
		//IF IT DOESNT EXIST CREATE ONE
		if (!ptr_myfile)
		{
		    fclose(ptr_myfile);
			ptr_myfile=fopen("data.bin","wb");
			fwrite(scores, sizeof(int)*10, 1, ptr_myfile);
            fclose(ptr_myfile);
            ptr_myfile=fopen("data.bin","rb");
		}
		//READ THE HIGH SCORES DATA FROM THE FILE
        fread(scores,sizeof(int)*10,1,ptr_myfile);

	//==============================================
    //MAIN GAME LOOP
    //==============================================
    ALLEGRO_EVENT ev;
	while(!done){

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
                if(!pressed){

		case ALLEGRO_KEY_LEFT:      pressed=true; keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     pressed=true; keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        pressed=true; keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      pressed=true; keys[DOWN] = true; break;
		case ALLEGRO_KEY_SPACE:     pressed=true; keys[SPACE] = true; break;
		case ALLEGRO_KEY_ENTER:     pressed=true; keys[SPACE] = true; break;

                }
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {

        case ALLEGRO_KEY_LEFT:       keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT:      keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP:         keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN:       keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE:      keys[SPACE] = false;  break;
        case ALLEGRO_KEY_ENTER:      keys[SPACE] = false;  break;
        pressed = false;
        } }
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(al_is_event_queue_empty(event_queue)){

            if(keys[DOWN]){
                if(selected == 1) selected=0; else selected++;
            }else if(keys[UP]){
                if(selected == 0) selected=1; else selected--;
            }

            if(keys[SPACE]){
                    if(selected){
                        done = true;
                    }else{
                        for(i=0;i<10;i++){
                            scores[i] = 0;
                        }
                ptr_myfile=fopen("data.bin","wb");
                fwrite(scores, sizeof(int)*10, 1, ptr_myfile);
                fclose(ptr_myfile);
                    }

            }
        al_draw_text(font22, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-250, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");

        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-220, ALLEGRO_ALIGN_CENTRE, "1- %d",scores[0]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-200, ALLEGRO_ALIGN_CENTRE, "2- %d",scores[1]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-180, ALLEGRO_ALIGN_CENTRE, "3- %d",scores[2]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-160, ALLEGRO_ALIGN_CENTRE, "4- %d",scores[3]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-140, ALLEGRO_ALIGN_CENTRE, "5- %d",scores[4]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-120, ALLEGRO_ALIGN_CENTRE, "6- %d",scores[5]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "7- %d",scores[6]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-80, ALLEGRO_ALIGN_CENTRE, "8- %d",scores[7]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "9- %d",scores[8]);
        al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTRE, "10- %d",scores[9]);


             switch(selected){
        case 0:
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "RESET SCORES");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;
        case 1:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "RESET SCORES");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;

                   break;
            }

            keys[LEFT] = false;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
            keys[SPACE] = false;

			al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
		}

		al_wait_for_event(event_queue, &ev);
	}

    if(selected == 1){
        return 2;
    }
}

int gameOver(){

	al_reserve_samples(isMusicsOpen);
    al_play_sample(menuMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    bool done = false;
    bool pressed = false;
    int someInt = 0;
    int selected = 0;
    int scores[10] = {0,0,0,0,0,0,0,0,0,0};

        int i,k;
		FILE *ptr_myfile;
        //READ HIGH SCORES FILE
		ptr_myfile=fopen("data.bin","rb");
		//IF IT DOESNT EXIST CREATE ONE
		if (!ptr_myfile)
		{
		    fclose(ptr_myfile);
			ptr_myfile=fopen("data.bin","wb");
			fwrite(scores, sizeof(int)*10, 1, ptr_myfile);
            fclose(ptr_myfile);
            ptr_myfile=fopen("data.bin","rb");
		}
		//READ THE HIGH SCORES DATA FROM THE FILE
        fread(scores,sizeof(int)*10,1,ptr_myfile);

        //PUTH THE SCORE IN A RIGHT POSITION
        for(i=0;i<10;i++){
            if(totalScore>scores[i]){
                for(k=9;k>i;k--) scores[k] = scores[k-1];
                scores[i]=totalScore;
                fclose(ptr_myfile);
                break;
            }
        }
        //SAVE HIGH SCORES FILE
        ptr_myfile=fopen("data.bin","wb");
        fwrite(scores, sizeof(int)*10, 1, ptr_myfile);
        fclose(ptr_myfile);

	//==============================================
    //MAIN GAME LOOP
    //==============================================
    ALLEGRO_EVENT ev;
	while(!done){

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
                if(!pressed){

		case ALLEGRO_KEY_LEFT:      pressed=true; keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     pressed=true; keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        pressed=true; keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      pressed=true; keys[DOWN] = true; break;
		case ALLEGRO_KEY_SPACE:     pressed=true; keys[SPACE] = true; break;
		case ALLEGRO_KEY_ENTER:     pressed=true; keys[SPACE] = true; break;

                }
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {

        case ALLEGRO_KEY_LEFT:       keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT:      keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP:         keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN:       keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE:      keys[SPACE] = false;  break;
        case ALLEGRO_KEY_ENTER:      keys[SPACE] = false;  break;
        pressed = false;
        } }
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(al_is_event_queue_empty(event_queue)){

            if(keys[DOWN]){
                if(selected == 2) selected=0; else selected++;
            }else if(keys[UP]){
                if(selected == 0) selected=2; else selected--;
            }

            if(keys[SPACE]){
                done = true;
            }



        al_draw_text(font22, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-250, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-180, ALLEGRO_ALIGN_CENTRE, "Your Score");
        al_draw_textf(font34, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-140, ALLEGRO_ALIGN_CENTRE, "%d",totalScore);

        if(i<10){
             al_draw_textf(font13, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-90, ALLEGRO_ALIGN_CENTRE, "You are the %d. on the high scores list.",i+1);
        }

             switch(selected){
        case 0:
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "PLAY AGAIN");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "EXIT GAME");
                   break;
        case 1:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "PLAY AGAIN");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "EXIT GAME");
                   break;
        case 2:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "PLAY AGAIN");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "MAIN MENU");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "EXIT GAME");
                   break;
            }

            keys[LEFT] = false;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
            keys[SPACE] = false;

			al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
		}

		al_wait_for_event(event_queue, &ev);


	}


if(selected == 1){
    return 2;
}
if(selected == 2){
    return 0;
}
if(selected == 0){
    return 1;
}

}







int settings(){



  bool done = false;
    bool pressed = false;
    int selected = 0;

	//==============================================
    //MAIN GAME LOOP
    //==============================================
    ALLEGRO_EVENT ev;
	while(!done){

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
                if(!pressed){

		case ALLEGRO_KEY_LEFT:      pressed=true; keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     pressed=true; keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        pressed=true; keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      pressed=true; keys[DOWN] = true; break;
		case ALLEGRO_KEY_SPACE:     pressed=true; keys[SPACE] = true; break;
		case ALLEGRO_KEY_ENTER:     pressed=true; keys[SPACE] = true; break;

                }
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {

        case ALLEGRO_KEY_LEFT:       keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT:      keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP:         keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN:       keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE:      keys[SPACE] = false;  break;
        case ALLEGRO_KEY_ENTER:      keys[SPACE] = false;  break;
        pressed = false;
        } }
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(al_is_event_queue_empty(event_queue)){

            if(keys[DOWN]){
                if(selected == 4) selected=0; else selected++;
            }else if(keys[UP]){
                if(selected == 0) selected=4; else selected--;
            }

            if(keys[SPACE]){
                    if(selected == 0){
                    isMusicsOpen = !isMusicsOpen;
                    al_stop_samples();
                    al_reserve_samples(0);
                    }else if(selected == 1){
                    isSoundsOpen = !isSoundsOpen;
                    }else if(selected == 2){
                    isBackgroundOpen = !isBackgroundOpen;
                    }else if(selected == 3){
                        if(isFullScreen){

                            shutdownSystem();
                            initSystem(FALSE);

                        }else{
                           shutdownSystem();
                            initSystem(TRUE);

                        }
                    //isFullScreen = !isFullScreen;
                    }else{
                    done = true;
                    }
            }

        al_draw_text(font30, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-250, ALLEGRO_ALIGN_CENTRE, "SETTINGS");


        if(isMusicsOpen){

            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "ON");

        }else{
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "OFF");

        }
        if(isSoundsOpen){
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "ON");


        }else{
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "OFF");

        }

        if(isBackgroundOpen){
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "ON");


        }else{
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "OFF");

        }



        if(isFullScreen){
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "ON");


        }else{
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2+100, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "OFF");

        }







             switch(selected){
        case 0:
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "MUSIC : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "SOUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "BACKGROUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "GO BACK");
            break;
        case 1:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "MUSIC : ");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "SOUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "BACKGROUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "GO BACK");
            break;
        case 2:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "MUSIC : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "SOUND : ");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "BACKGROUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "GO BACK");
            break;
        case 3:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "MUSIC : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "SOUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "BACKGROUND : ");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "GO BACK");
            break;
        case 4:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-60, ALLEGRO_ALIGN_CENTRE, "MUSIC : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-30, ALLEGRO_ALIGN_CENTRE, "SOUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "BACKGROUND : ");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN : ");
            al_draw_text(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2+60, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;


            }

            keys[LEFT] = false;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
            keys[SPACE] = false;

			al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
		}

		al_wait_for_event(event_queue, &ev);


	}


if(selected == 4){
    return 2;
}

}





int shipSelect(){


  bool done = false;
    bool pressed = false;
    int someInt = 0;
    int selected = 0;

	//==============================================
    //MAIN GAME LOOP
    //==============================================
    ALLEGRO_EVENT ev;
	while(!done){

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
                if(!pressed){

		case ALLEGRO_KEY_LEFT:      pressed=true; keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     pressed=true; keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        pressed=true; keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      pressed=true; keys[DOWN] = true; break;
		case ALLEGRO_KEY_SPACE:     pressed=true; keys[SPACE] = true; break;
		case ALLEGRO_KEY_ENTER:     pressed=true; keys[SPACE] = true; break;

                }
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {

        case ALLEGRO_KEY_LEFT:       keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT:      keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP:         keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN:       keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE:      keys[SPACE] = false;  break;
        case ALLEGRO_KEY_ENTER:      keys[SPACE] = false;  break;
        pressed = false;
        } }
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(al_is_event_queue_empty(event_queue)){

            if(keys[DOWN]){
                if(selected == 3) selected=0; else selected++;
            }else if(keys[UP]){
                if(selected == 0) selected=3; else selected--;
            }

            if(keys[SPACE]){
                done = true;
                if(selected == 0){
                    player.type = missileShip;
                    player.image = controllableImage;
                    player.w = al_get_bitmap_width(controllableImage)/4;
                    player.h = al_get_bitmap_height(controllableImage)/4;
                }else if(selected == 1){
                    player.type = laserShip;
                    player.image = controllable2Image;
                    player.w = al_get_bitmap_width(controllable2Image)/4;
                    player.h = al_get_bitmap_height(controllable2Image)/4;
                }else if(selected == 2){
                    player.type = lightningShip;
                    player.image = controllable3Image;
                    player.w = al_get_bitmap_width(controllable3Image)/4;
                    player.h = al_get_bitmap_height(controllable3Image)/4;
                }
            }
        al_draw_text(font22, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT/2-250, ALLEGRO_ALIGN_CENTRE, "SELECT A SHIP");


            al_draw_scaled_rotated_bitmap(controllableImage,0, 0,WIDTH/2-15, HEIGHT/2-140, 0.30, 0.30,0, 0);
            al_draw_scaled_rotated_bitmap(controllable2Image,0, 0,WIDTH/2-25, HEIGHT/2-40, 0.30, 0.30,0, 0);
            al_draw_scaled_rotated_bitmap(controllable3Image,0, 0,WIDTH/2-20, HEIGHT/2+50, 0.30, 0.30,0, 0);




             switch(selected){
        case 0:


            al_draw_text(font18, al_map_rgb(255, 0, 0),     WIDTH / 2,     HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "MISSILE SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "LAZER SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+100, ALLEGRO_ALIGN_CENTRE, "LIGHTENING SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+140, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;
        case 1:


            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "MISSILE SHIP");
            al_draw_text(font18, al_map_rgb(255, 0, 0),     WIDTH / 2,     HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "LAZER SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+100, ALLEGRO_ALIGN_CENTRE, "LIGHTENING SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+140, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;
        case 2:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "MISSILE SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "LAZER SHIP");
            al_draw_text(font18, al_map_rgb(255, 0, 0),     WIDTH / 2,     HEIGHT/2+100, ALLEGRO_ALIGN_CENTRE, "LIGHTENING SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+140, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;
        case 3:
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2-100, ALLEGRO_ALIGN_CENTRE, "MISSILE SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "LAZER SHIP");
            al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/2+100, ALLEGRO_ALIGN_CENTRE, "LIGHTENING SHIP");
            al_draw_text(font18, al_map_rgb(255, 0, 0),     WIDTH / 2,     HEIGHT/2+140, ALLEGRO_ALIGN_CENTRE, "GO BACK");
                   break;
            }

            keys[LEFT] = false;
            keys[RIGHT] = false;
            keys[UP] = false;
            keys[DOWN] = false;
            keys[SPACE] = false;

			al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
		}

		al_wait_for_event(event_queue, &ev);


	}
if(selected == 3){
    return 2;
}else{
    return 1;
}


}

