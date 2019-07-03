#include "Machete.h"

Machete::Machete(SDL_Texture* t){
    texture = t;
    dst.x = (960/2) + 75;
    dst.y = 640-250;
    dst.w = 90;
    dst.h = 200;
}

void Machete::update(){
    if(active){
        dst.x -= 10;
    }
}

void Machete::draw(SDL_Renderer* r){
    if(active){
        SDL_RenderCopyEx(r, texture, NULL, &dst, 0, 0, SDL_FLIP_NONE);
    }
}

void Machete::handle_events(SDL_Event event){
    switch (event.type)
    {
        case SDL_KEYDOWN:
            if(!key_press){
                key_press = true;

                switch(event.key.keysym.sym){
                    case SDLK_f:
                        active = true;
                    break;
                }
            }
        break;

       case SDL_KEYUP:
           key_press = false;
           active = false;
           dst.x = (960/2) + 75;
           dst.y = 640-250;
       break;
    }
}

bool Machete::isActive(){
    return active;
}
