#ifndef AIM_H
#define AIM_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Bullet.h"

class Aim
{
public:
    Aim(SDL_Texture* t){
        texture = t;
    }

    void draw(SDL_Renderer* r);
    void handle_events(SDL_Event event, Bullet& bullet);
    void kill(){killed++; std::cout << "Enemies killed: " << killed << "\n";;}

    bool isAiming(){return aiming;}
    void aim(){aiming = !aiming;}
    int getBullets(){return bullets;}
    int getMeters(){return meters;}

    int life = 100;
private:
    SDL_Texture* texture = NULL;
    SDL_Rect dst = {0,0,2400,2400};
    bool aiming = false, buttonPressed = false, keyPressed = false;

    int killed = 0;
    int meters = 4700;
    int bullets = 5;
    int cartuchos = 10;
};

#endif // AIM_H
