#ifndef PARTICLES_H
#define PARTICLES_H

#include <SDL2/SDL.h>
#include <iostream>

struct Prtcl{
    SDL_Rect particles[130];
    int velx, vely;
};

class Particles
{
public:
    void split(int x, int y, int xmax, int ymax, int w, int h);

    void update();
    void zoom();

    void draw(SDL_Renderer* r);

    bool isActive();

    void activate();
    void deactivate();


private:
    Prtcl p;
    bool active = false;
    int ylim;
    int last_w, last_h;

};

#endif // PARTICLES_H
