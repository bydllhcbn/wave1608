#ifndef _F_H
#define _F_H

void createAnimation(float x,float y,int maxFrame,int frameDelay,int frameWidth,int frameHeight,ALLEGRO_BITMAP *sheet);
int removeAnimation(int id);
void createBullet(float x,float y,float velX,float velY,int type,ALLEGRO_BITMAP *image,int damage);
int removeBullet(int id);
int removeEnemy(int id);
int getBulletCount(Bullet * head);
Enemy * nearestEnemy();
Enemy * createEnemy(float x,float y,float velX,float velY,int health,int fireSpeed,int damage,
                    ALLEGRO_BITMAP *image,bool followPath,bool followPlayer);
                  int removeEnemy(int id);
                  int randomNumber(int n);
                  int randomDecision();
                  void createEnemiesByTime();
                  double distance(int x1,int y1,int x2,int y2);
#endif
