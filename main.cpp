#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Bullet.h"
#include "Particles.h"
#include "Enemy.h"

#define LOG_COMMENT(msg) std::cout << msg << "\n";

const int sw = 960;
const int sh = 540;
Game game;
SDL_Event event;
SDL_Texture* aimT = NULL;


class Aim
{
};

int main(int argc, char* args[])
{
    const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
    int frameTime;
    int frames = 0;

    game.init("Don't go back", sw,sh);

     SDL_ShowCursor(SDL_DISABLE);

    //aim
    SDL_Surface* s = IMG_Load("assets/aim2.png");
    aimT = SDL_CreateTextureFromSurface(game.renderer, s);
    SDL_FreeSurface(s);
    SDL_Rect src = {0,0,600,600};
    SDL_Rect dst = {0,0,2400,2400};

    //desert
//    s = IMG_Load("assets/desert.png");
//    background = SDL_CreateTextureFromSurface(game.renderer, s);
//    SDL_FreeSurface(s);
//    SDL_Rect srcBack = {0,0,900,500};
//    SDL_Rect dstBack = {0,0,sw,sh};

    SDL_Rect sand = {0,sh/2,sw,sh/2};
    SDL_Rect sky = {0,0,sw,sh/2};

    //goal
    SDL_Rect goal = {0, sh/2, sw, 2};

    Bullet bullet;

    bool aiming = false;
    bool buttonPressed = false;
    bool keyPressed = false;
    bool hurt = false;

    //enemies
    Enemy enemy = Enemy(500/2, 500/2+15, 1, 5, (rand()%5)+1 );
    Enemy enemy1 = Enemy((500/2)-64, 500/2+15, 1, 5, (rand()%5)+1 );
    Enemy enemy2 = Enemy((500/2)+64, 500/2+15, 1, 5, (rand()%5)+1 );

    std::vector<Enemy*> enemies = {&enemy, &enemy1, &enemy2};
    LOG_COMMENT(enemies.size());

    Particles particles;

    //timers
    unsigned int seconds = 0;
    int fl = 0;
    int lastSeconds = 0;
    //timers

    int totalenemies = 3;
    int killed = 0;
    int meters = 6700;
    int life = 100;
    int bullets = 5;
    int cartuchos = 5;

    while(game.running){
        SDL_RenderClear(game.renderer);

        frameStart = SDL_GetTicks();
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT :
                game.running = false;
                break;
            case SDL_KEYDOWN:
                if(!keyPressed){
                    keyPressed = true;

                    switch(event.key.keysym.sym){
                        case SDLK_w:
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->closer();
                                if(meters > 0){
                                    meters--;
                                    if(meters %100 == 0){
                                        std::cout << "meters left: " << meters << "\n";
                                    }

                                    if(meters < 4700){
                                        if((meters/2)%100 == 0){
                                            goal.h += 3;
                                            goal.y -= 3;
                                        }
                                    }
                                }

                                if(meters == 0){
                                    LOG_COMMENT("YOU REACH THE GOAL");
                                }
                            }
                            keyPressed = false;
                        break;
                        case SDLK_s:
//                            for(unsigned int i = 0; i<enemies.size(); i++){
//                                enemies[i]->go_back();
//                                meters++;
//                                if(meters < 4700){
//                                    if((meters/2)%100 == 0){
//                                        goal.h -= 3;
//                                        goal.y += 3;
//                                    }
//                                }
//
//                            }
//
//                            keyPressed = false;
                        break;
                        case SDLK_d:
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->mov(1);
                            }
                            keyPressed = false;
                        break;
                        case SDLK_a:
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->mov(0);
                            }
                            keyPressed = false;
                        break;
                        case SDLK_r:
                            if(cartuchos > 0){
                                cartuchos--;
                                std::cout << "carts: " << cartuchos << "\n";
                                bullets = 5;
                                if(aiming){
                                     //aiming = false;
                                }
                            } else {
                                LOG_COMMENT("RUN");
                            }
                        break;
                        case SDLK_h:
                            hurt = !hurt;
                        break;
                    }

                }
                break;

            case SDL_KEYUP:
                keyPressed = false;
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(!buttonPressed){
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        if(!aiming){
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->zoom();
                            }
                        }
                        if(aiming){
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->dezoom();
                            }
                        }
                        particles.deactivate();
                        aiming = !aiming;
                        buttonPressed = true;
                    }

                    if(event.button.button == SDL_BUTTON_LEFT){
                        if(bullets > 0){
                            bullet.setxy(event.button.x,event.button.y);
                            bullet.change_state();
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                if(enemies[i]->isInside(bullet)){
                                    enemies[i]->kill();
                                    killed++;
                                    std::cout << "Enemies killed: " << killed << "\n";

                                    bullet.change_state();

                                    //particles.split(event.button.x-10,event.button.y-15,event.button.x+10,enemies[i]->getYmax(), 1,1);
                                    particles.split(enemies[i]->getX(),enemies[i]->getY(),enemies[i]->getXmax(),enemies[i]->getYmax(), 2,2);

                                    particles.activate();
                                    LOG_COMMENT("SHOOTEED");
                                    break;
                                }
                            }

                            if(bullet.isActive()){
                                bullet.change_state();
                            }
                            if(!aiming){

                            }
                            if(aiming){
                                for(unsigned int i = 0; i<enemies.size(); i++){
                                    enemies[i]->dezoom();
                                }
                                aiming = !aiming;
                            }

                            buttonPressed = true;
                            bullets--;
                            std::cout << "bullets: " << bullets << "\n";
                        } else {
                            LOG_COMMENT("Out of ammo. Press R.");
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:

                dst.x = event.button.x-1200;
                dst.y = event.button.y-1200;

                break;
            case SDL_MOUSEBUTTONUP:
                buttonPressed = false;
                break;
            default:
                break;
        }

//        SDL_RenderCopy(game.renderer, background, &srcBack, &dstBack);
        SDL_SetRenderDrawColor(game.renderer, 220, 198, 160,0);
        SDL_RenderFillRect(game.renderer, &sand);

        SDL_SetRenderDrawColor(game.renderer, 0,0,0,255);


        hurt = false;
        for(unsigned int i = 0; i<enemies.size(); i++){
            if(enemies[i]->hurt(life, frames) && enemies[i]->isActive()){
                if(!aiming){
                    std::cout << "life: " << life << "\n";
                    hurt = true;
                }
            }
        }

        for(unsigned int i = 0; i<enemies.size(); i++){
            enemies[i]->draw(game.renderer);
        }

        SDL_SetRenderDrawColor(game.renderer, 135, 206, 235,0);
        SDL_RenderFillRect(game.renderer, &sky);

        if(meters < 4700){
            SDL_SetRenderDrawColor(game.renderer, 125,125,0,0);
            SDL_RenderFillRect(game.renderer, &goal);
        }

        if(particles.isActive()){
            particles.update();
            particles.draw(game.renderer);
        }

        if(aiming){
            SDL_RenderCopy(game.renderer, aimT, &src, &dst);
        }
        SDL_SetRenderDrawColor(game.renderer, 255,255,255,255);

        if(frames == 30){
            for(unsigned int i = 0; i < enemies.size(); i++){
                enemies[i]->update();
            }
        }

        if(hurt){
            SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(game.renderer, 255,0,0,75);
            SDL_Rect a = {0,0,sw,sh};
            SDL_RenderFillRect(game.renderer, &a);
            SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);
        }

        frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
        }

        frames++;
        if(frames > 60){
            frames = 0;
        }

        seconds = SDL_GetTicks()/1000;

        if(seconds-lastSeconds == 5){
            lastSeconds = seconds;

            if(totalenemies < 15){
                for(int i = 0; i<6; i++){
                    enemies.push_back(new Enemy((rand()%sw), (500/2)+15, 1, 5, (rand()%5)+1));
                    totalenemies++;
                }
            }
        }

        SDL_RenderPresent(game.renderer);
    }

    game.clean();

    return 0;
}
