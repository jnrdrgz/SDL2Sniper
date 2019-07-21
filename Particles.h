#ifndef PARTICLES_H
#define PARTICLES_H

#include "SDL2/SDL.h"
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

    void handle_events(SDL_Event event, bool aiming){
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if(!keyPressed){
                    keyPressed = true;

                    switch(event.key.keysym.sym){
                        case SDLK_w:
                            deactivate();

                            keyPressed = false;
                        break;
                        case SDLK_d:
                            deactivate();
                            keyPressed = false;
                        break;
                        case SDLK_a:
                            deactivate();
                            keyPressed = false;
                        break;
                    }
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(!buttonPressed){
                    buttonPressed = true;
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        deactivate();
                    }
                }
            break;
        }
    }

private:
    Prtcl p;
    bool active = false, keyPressed = false, buttonPressed = false;
    int ylim;
    int last_w, last_h;

};

#endif // PARTICLES_H
