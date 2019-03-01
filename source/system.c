#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "init.h"
#include "system.h"

void initSystem(bool fullscreen){
    //==============================================
	//INITIALIZE SYSTEM
	//==============================================
	if(!al_init()) return -1;

	if(fullscreen){
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	}else{
        al_set_new_display_flags(ALLEGRO_WINDOWED);
	}
	display = al_create_display(WIDTH, HEIGHT);
    al_set_window_title(display,"Wave: 1608  (Summer Homework)");
    isSoundsOpen = TRUE;
    isMusicsOpen = TRUE;
    isBackgroundOpen = TRUE;
    isFullScreen = fullscreen;
	if(!display) return -1;


	//==============================================
	//INITIALIZE ADDONS
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
    al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(0);

	//==============================================
	//TIMER INIT AND STARTUP EVENT SYSTEM
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

        font22 = al_load_font("img/DejaVuSans.ttf", 22, 0);
        font18 = al_load_font("img/DejaVuSans.ttf", 18, 0);
        font10 = al_load_font("img/DejaVuSans.ttf", 10, 0);
        font13 = al_load_font("img/DejaVuSans.ttf", 13, 0);
        font30 = al_load_font("img/DejaVuSans.ttf", 30, 0);
        font34 = al_load_font("img/DejaVuSans.ttf", 34, 0);

        logo = al_load_bitmap("img/logo.png");
        enemy1Image = al_load_bitmap("img/enemy1.png");
        enemy2Image = al_load_bitmap("img/enemy2.png");
        enemy3Image = al_load_bitmap("img/enemy3.png");
        enemy4Image = al_load_bitmap("img/enemy4.png");
        enemy5Image = al_load_bitmap("img/enemy5.png");
        missileImage = al_load_bitmap("img/missile.png");
        fireImage = al_load_bitmap("img/fire.png");
        controllableImage = al_load_bitmap("img/player.png");
        controllable2Image = al_load_bitmap("img/player2.png");
        controllable3Image = al_load_bitmap("img/player3.png");
        explosion = al_load_bitmap("img/explosion.png");
        spaceBackground = al_load_bitmap("img/space.png");
        spaceStars = al_load_bitmap("img/stars4.png");
        bulletExplosion = al_load_bitmap("img/bulletExplosion.png");
        lightningImage = al_load_bitmap("img/lightning.png");
        laserImage = al_load_bitmap("img/laser.png");
        menuMusic = al_load_sample( "sounds/menu.wav" );
        gameMusic = al_load_sample( "sounds/main.wav" );
        explosionSound1= al_load_sample( "sounds/explo1.wav" );
        explosionSound2= al_load_sample( "sounds/explo2.wav" );
        gunSound1 = al_load_sample( "sounds/gun1.wav" );
        gunSound2 = al_load_sample( "sounds/gun2.wav" );
        laserSound = al_load_sample( "sounds/laser.ogg" );
        lightningSound = al_load_sample( "sounds/lightning.wav" );
        missileSound = al_load_sample( "sounds/missile.wav" );
        al_set_display_icon(display,controllableImage);
}

void shutdownSystem(){
    //==============================================
	//DESTROY THEM ALL
	//==============================================
	al_destroy_bitmap(laserImage);
	al_destroy_bitmap(lightningImage);
	al_destroy_bitmap(bulletExplosion);
	al_destroy_bitmap(spaceStars);
	al_destroy_bitmap(spaceBackground);
	al_destroy_bitmap(explosion);
	al_destroy_bitmap(controllable3Image);
	al_destroy_bitmap(controllable2Image);
	al_destroy_bitmap(controllableImage);
	al_destroy_bitmap(fireImage);
	al_destroy_bitmap(missileImage);
	al_destroy_bitmap(logo);
	al_destroy_bitmap(enemy1Image);
	al_destroy_bitmap(enemy2Image);
	al_destroy_bitmap(enemy3Image);
	al_destroy_bitmap(enemy4Image);
	al_destroy_bitmap(enemy5Image);

	al_destroy_font(font10);
	al_destroy_font(font13);
	al_destroy_font(font18);
	al_destroy_font(font22);
	al_destroy_font(font30);
	al_destroy_font(font34);
	al_destroy_timer(timer);

	al_destroy_sample(menuMusic);
	al_destroy_sample(gameMusic);
	al_destroy_sample(explosionSound1);
	al_destroy_sample(explosionSound2);
	al_destroy_sample(gunSound1);
	al_destroy_sample(gunSound2);
	al_destroy_sample(laserSound);
	al_destroy_sample(lightningSound);
	al_destroy_sample(missileSound);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}

int startGame(){
    al_stop_samples();
    if(isMusicsOpen){
       // al_reserve_samples(1);
        al_play_sample(gameMusic, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    }
    //===============================================================00
    //========================INITIALIZE GAME========================00
                                initialize();
    //========================INITIALIZE GAME========================00
    //===============================================================00
    al_start_timer(timer);
    isGameOver = false;
	bool isItTime = false;
    bool pressed = false;


	//==============================================
    //MAIN GAME LOOP
    //==============================================

	while(!isGameOver){
    ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		//==============================================
		//HANDLE INPUT AND RENDER TO UPDATE (Only Space,Escape,Arrow Keys,W,A,S,D Will be Handled)
		//==============================================
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE: isGameOver = true; break;
		case ALLEGRO_KEY_LEFT:      keys[LEFT] = true; break;
		case ALLEGRO_KEY_A:         keys[LEFT] = true; break;
		case ALLEGRO_KEY_RIGHT:     keys[RIGHT] = true; break;
		case ALLEGRO_KEY_D:         keys[RIGHT] = true; break;
		case ALLEGRO_KEY_UP:        keys[UP] = true; break;
		case ALLEGRO_KEY_W:         keys[UP] = true; break;
		case ALLEGRO_KEY_DOWN:      keys[DOWN] = true; break;
		case ALLEGRO_KEY_S:         keys[DOWN] = true; break;
        case ALLEGRO_KEY_G: al_set_timer_count(timer,1.0/10.0);  break;
		case ALLEGRO_KEY_SPACE:   if(!pressed) {pressed=true; autoPilotOn = !autoPilotOn; keys[SPACE] = true;} break;
		 } } else if(ev.type == ALLEGRO_EVENT_KEY_UP) { switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE: isGameOver = true; break;
        case ALLEGRO_KEY_LEFT: keys[LEFT] = false; break;
        case ALLEGRO_KEY_A: keys[LEFT] = false; break;
        case ALLEGRO_KEY_RIGHT: keys[RIGHT] = false; break;
        case ALLEGRO_KEY_D: keys[RIGHT] = false; break;
        case ALLEGRO_KEY_UP: keys[UP] = false; break;
        case ALLEGRO_KEY_W: keys[UP] = false; break;
        case ALLEGRO_KEY_DOWN: keys[DOWN] = false; break;
        case ALLEGRO_KEY_S: keys[DOWN] = false; break;
        case ALLEGRO_KEY_SPACE: pressed = false; keys[SPACE] = false;  break;
        case ALLEGRO_KEY_G: al_set_timer_count(timer,1.0/60.0);  break;
        } }else if(ev.type == ALLEGRO_EVENT_TIMER){isItTime = true;}
		//==============================================
		//RENDER AND UPDATE
		//==============================================
		if(isItTime && al_is_event_queue_empty(event_queue)){isItTime = false;

            //==============================================
            //HANDLE TIME
            //==============================================
            TIME=al_get_timer_count(timer);

            //===============================================================00
            //========================UPDATE GAME==========================00
                                        update();
            //========================UPDATE GAME==========================00
            //===============================================================00
			al_flip_display();

			//redrawing all objects 60 times for every one second
            al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	//GAME MUST HAVE FINISHED
	//RESET EVERYTHING
	removeAll();
    al_stop_samples();
    totalScore += TIME/10;
    al_set_timer_count(timer,0);
    al_stop_timer(timer);
    enemyCount = 0;
    bulletCount = 0;
    autoPilotOn = FALSE;
return 4;
}
