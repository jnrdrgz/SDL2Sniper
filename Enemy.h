#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "Bullet.h"
#include "Game.h"

class Enemy
{
public:
    Enemy(){};
    ~Enemy(){
        dst.w = 0;
        dst.h = 0;
        //SDL_DestroyTexture(texture);
    }

    Enemy(int x, int y, int w, int h, int vel);
    Enemy(int x, int y, int w, int h, int vel, SDL_Texture* t);

    int getX();
    int getY();
    int getYmax();
    int getXmax();
    void closer();
    void walk();
    void mov(int dir);
    void go_back();
    void zoom();
    void dezoom();
    void kill();
    void update();
    bool isActive();
    bool isInside(Bullet b);
    bool hurt(int &health, int f);

    void set_texture(SDL_Texture* t);
    void draw(SDL_Renderer* r);
private:
    SDL_Rect src, dst;
    SDL_Texture* texture = NULL;
    int vel, last_w, last_h;
    bool active;
};

#endif // ENEMY_H
