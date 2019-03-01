#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#ifndef _INIT_H
#define _INIT_H


//defining and declaring are DIFFEEERENT
//Sadly only declarings are here (so low)
//


enum controllableType{missileShip,laserShip,lightningShip};
typedef struct Animation{
    int id;
    float x;
    float y;
	int curFrame;//0
	int frameCount;//0
	int maxFrame;
	int frameDelay;//5
	int frameWidth;
	int frameHeight;
	bool looped;
    ALLEGRO_BITMAP *sheet;//Oh sheet
    struct Animation * next;
} Animation;

typedef struct Player{
	float x;
	float y;
	float velX;
	float velY;
    int health;
    int speed;
    int damage;
	int w;
	int h;
	enum controllableType type;
    ALLEGRO_BITMAP *bulletImage;
	ALLEGRO_BITMAP *image;
} Player;

typedef struct Enemy{
    int id;
	float x;
	float y;
	float velX;
	float velY;
	int maxY;
    int w;
	int h;
    int health;
    int fireSpeed;
    int damage;
	bool followPlayer;
    bool followPath;
    int path[5];
    ALLEGRO_BITMAP *bulletImage;
	ALLEGRO_BITMAP *image;
	struct Enemy * next;
} Enemy;

typedef struct Bullet{
    int id;
    float x;
    float y;
    float velX;
    float velY;
    int type; //0 US 1 Enemy
    int width;
    int height;
    float rotation;
    int damage;
    ALLEGRO_BITMAP *image;

    struct Bullet * next;
} Bullet;
ALLEGRO_FONT *font18;
ALLEGRO_FONT *font22;
ALLEGRO_FONT *font30;
ALLEGRO_FONT *font34;
ALLEGRO_FONT *font10;
ALLEGRO_FONT *font13;
Player player;
Bullet * bulletHead;
Enemy * enemyHead;
Animation * animationHead;
int bulletAI;       // Auto Increment (Every bullet will have a distinct ID thaks sql :)
int enemyAI;       // Auto Increment for enemies
int animationAI;       // Auto Increment for enemies
extern const int WIDTH;
extern const int HEIGHT;
extern int enemyCount;
extern int bulletCount;
int playerHealth;
int playerLives;
int maxBullets;
int totalScore;
bool isGameOver;
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
enum TO{toMENU};
enum GUN_TYPE{NONE,MISSILE,LAZER,LIGHTENING};
int keys[5];
int TIME;
int waitFor;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP * logo;
ALLEGRO_BITMAP * ship1Image;
ALLEGRO_BITMAP * ship2Image;
ALLEGRO_BITMAP * fireImage;
ALLEGRO_BITMAP * bulletImage;
ALLEGRO_BITMAP * lazerImage;
ALLEGRO_BITMAP * enemy1Image;
ALLEGRO_BITMAP * enemy2Image;
ALLEGRO_BITMAP * enemy3Image;
ALLEGRO_BITMAP * enemy4Image;
ALLEGRO_BITMAP * enemy5Image;
ALLEGRO_BITMAP * missileImage;
ALLEGRO_BITMAP * controllableImage;
ALLEGRO_BITMAP * controllable2Image;
ALLEGRO_BITMAP * controllable3Image;
ALLEGRO_BITMAP * explosion;
ALLEGRO_BITMAP * spaceBackground;
ALLEGRO_BITMAP * spaceStars;
ALLEGRO_BITMAP * bulletExplosion;
ALLEGRO_BITMAP * lightningImage;
ALLEGRO_BITMAP * laserImage;
ALLEGRO_SAMPLE *menuMusic;
ALLEGRO_SAMPLE *gameMusic;
ALLEGRO_SAMPLE *explosionSound1;
ALLEGRO_SAMPLE *explosionSound2;
ALLEGRO_SAMPLE *gunSound1;
ALLEGRO_SAMPLE *gunSound2;
ALLEGRO_SAMPLE *laserSound;
ALLEGRO_SAMPLE *lightningSound;
ALLEGRO_SAMPLE *missileSound;
int initialize();
bool isSoundsOpen;
bool isMusicsOpen;
bool isBackgroundOpen;
bool isFullScreen;
bool autoPilotOn;

#endif

