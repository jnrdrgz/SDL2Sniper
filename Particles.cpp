#include "Particles.h"

 void Particles::split(int x, int y, int xmax, int ymax, int w, int h){
    for(int i = 0; i<130; i++){
        p.particles[i].x = rand()%(xmax-x + 1) + x;
        p.particles[i].y = rand()%(ymax-y + 1) + y;
        p.particles[i].w = w;
        p.particles[i].h = h;

        //p.velx = (rand()%5) - 2;
        p.vely = 1;
    }
    active = true;
    ylim = ymax+2;
}

void Particles::update(){
    if(active){
        for(int i = 0; i<130; i++){
            //p.particles[i].x += p.velx;
            if(!(p.particles[i].y + p.vely > ylim)){
                p.particles[i].y += p.vely;
            }
        }
    }
}

void Particles::zoom(){

    for(int i = 0; i<130; i++){
        if(p.particles[0].w < 30){
            p.particles[i].w += 3;
            p.particles[i].h += 3;
        }
        p.particles[i].x -= 1;
        p.particles[i].y -= 1;
    }

}

void Particles::draw(SDL_Renderer* r){
    for(int i = 0; i<130; i++){
        SDL_SetRenderDrawColor(r, 255,0,0,0);
        SDL_RenderFillRect(r, &p.particles[i]);
    }
}

bool Particles::isActive(){
    return active;
}

void Particles::activate(){
    active = true;
}

void Particles::deactivate(){
    active = false;
}


