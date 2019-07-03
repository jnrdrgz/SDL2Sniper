#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "Game.h"
#include "Bullet.h"
#include "Particles.h"
#include "Enemy.h"
#include "Machete.h"

#define LOG_COMMENT(msg) std::cout << msg << "\n";
#define Texture(t) textureManager.get_texture(t, game.renderer)

const int sw = 960;
const int sh = 540;
Game game;
SDL_Event event;
SDL_Texture* aimT = NULL;
TextureManager textureManager;

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

    game.init("Zombie Sniper", sw,sh);

     SDL_ShowCursor(SDL_DISABLE);

    aimT = Texture("assets/aim2.png");
    SDL_Rect dst = {0,0,2400,2400};

    Machete machete = Machete(Texture("assets/machete.png"));

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
    Enemy enemy = Enemy(500/2, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie.png") );
    Enemy enemy1 = Enemy((500/2)-64, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie.png") );
    Enemy enemy2 = Enemy((500/2)+64, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie.png") );

    std::vector<Enemy*> enemies = {&enemy, &enemy1, &enemy2};

    Particles particles;

    //timers
    unsigned int seconds = 0;
    int fl = 0;
    int lastSeconds = 0;
    //timers

    int totalenemies = 3;
    int killed = 0;
    int meters = 4000;
    int life = 100;
    int bullets = 5;
    int cartuchos = 10;

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
                            if(!aiming){
                                for(unsigned int i = 0; i<enemies.size(); i++){
                                    enemies[i]->closer();
                                }

                                particles.deactivate();

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
//                            keyPressed = false;
                        break;
                        case SDLK_d:
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->mov(1);
                            }
                            particles.deactivate();
                            keyPressed = false;
                        break;
                        case SDLK_a:
                            for(unsigned int i = 0; i<enemies.size(); i++){
                                enemies[i]->mov(0);
                            }
                            particles.deactivate();
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
                                    //break;
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

        machete.handle_events(event);
        SDL_SetRenderDrawColor(game.renderer, 220, 198, 160,0);
        SDL_RenderFillRect(game.renderer, &sand);

        SDL_SetRenderDrawColor(game.renderer, 0,0,0,255);


        hurt = false;
        for(unsigned int i = 0; i<enemies.size(); i++){
            if(enemies[i]->hurt(life, frames) && enemies[i]->isActive()){
                if(!aiming){
//                    std::cout << "life: " << life << "\n";
                    if(life == 0)
                        std::cout << "life: " << life << ". Death." << "\n";
                    hurt = true;
                }
            }
        }

        if(particles.isActive()){
            particles.update();
            particles.draw(game.renderer);
        }

        for(unsigned int i = 0; i<enemies.size(); i++){
            enemies[i]->draw(game.renderer);
        }

        SDL_SetRenderDrawColor(game.renderer, 135, 206, 235,0);
        SDL_RenderFillRect(game.renderer, &sky);

        machete.update();
        machete.draw(game.renderer);

        if(machete.isActive()){
            for(unsigned int i = 0; i<enemies.size(); i++){
                if(enemies[i]->hurt(fl, frames)){
                    if(enemies[i]->getX()>100 && enemies[i]->getX()<600){
                        enemies[i]->kill();
                    }
                }
            }
        }

        if(meters < 4700){
            SDL_SetRenderDrawColor(game.renderer, 125,125,0,0);
            SDL_RenderFillRect(game.renderer, &goal);
        }


        if(aiming){
            SDL_RenderCopy(game.renderer, aimT, NULL, &dst);
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

        if(seconds-lastSeconds == 15){
            lastSeconds = seconds;

            if(meters > 1500){
                for(int i = 0; i<10; i++){
                    enemies.push_back(new Enemy((rand()%sw), (500/2)+15, 1, 5, (rand()%5)+1, Texture("assets/zombie.png")));
                    totalenemies++;
                }
            }
        }

        SDL_RenderPresent(game.renderer);
    }

    game.clean();

    return 0;
}
