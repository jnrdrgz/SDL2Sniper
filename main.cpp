#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "Constants.h"
#include "Menu.h"

#include "TextureManager.h"
#include "Game.h"
#include "Bullet.h"
#include "Particles.h"
#include "Enemy.h"
#include "Machete.h"
#include "Aim.h"
#include "Audio.h"

#define LOG_COMMENT(msg) std::cout << msg << "\n";
#define Texture(t) textureManager.get_texture(t, game.renderer)

Game game;
SDL_Event event;
TextureManager textureManager;


int main(int argc, char* args[])
{
    const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
    int frameTime;
    int frames = 0;

    game.init("Zombie Sniper", sw,sh);
    SDL_Log("Game inited");

    Audio audio;

    SDL_ShowCursor(SDL_DISABLE);
    SDL_Log("cursor disabled");

    Machete machete = Machete(Texture("assets/machete.png"));
    SDL_Log("machete loaded");

    SDL_Rect sand = {0,sh/2,sw,sh/2};
    SDL_Rect sky = {0,0,sw,sh/2};
    SDL_Log("sand and sky");

    //goal
    SDL_Rect goal = {0, sh/2, sw, 2};
    SDL_Log("goal");

    bool buttonPressed = false;
    bool keyPressed = false;
    bool hurt = false;

    game_state state = MENU;
    Menu menu;
    SDL_Log("menu creted");
    menu.load();
    SDL_Log("menu loaded");
    menu.addItem(new MenuItem("PLAY", 0,0,0), game.renderer);
    menu.addItem(new MenuItem("OPTIONS", 0,0,0), game.renderer);
    menu.addItem(new MenuItem("EXIT", 0,0,0), game.renderer);
    SDL_Log("items added");

    
    SDL_Log("menu loaded");

    //enemies
    std::string enems[3] = {"assets/zombie1.png", "assets/zombie2.png", "assets/zombie3.png"};

    Enemy enemy = Enemy(500/2, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie1.png") );
    Enemy enemy1 = Enemy((500/2)-64, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie2.png") );
    Enemy enemy2 = Enemy((500/2)+64, 500/2+15, 1, 5, (rand()%5)+1, Texture("assets/zombie3.png") );
    SDL_Log("enemies loaded");

    std::vector<Enemy*> enemies = {&enemy, &enemy1, &enemy2};

    Aim aim = Aim(Texture("assets/aim2.png"));
    Bullet bullet;
    Particles particles;
    SDL_Log("aim particles and bullet");

    //timers
    unsigned int seconds = 0;
    int fl = 0;
    int lastSeconds = 0;
    //timers

    int totalenemies = 3;

    while(game.running){
        SDL_RenderClear(game.renderer);

        frameStart = SDL_GetTicks();
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                game.running = false;
                break;
            case SDL_KEYDOWN:
            	break;
        }


        if(state == MENU){
            SDL_SetRenderDrawColor(game.renderer, 135, 206, 235,0);
            SDL_RenderFillRect(game.renderer, &sky);

            SDL_SetRenderDrawColor(game.renderer, 220, 198, 160,0);
            SDL_RenderFillRect(game.renderer, &sand);

            state = (game_state)menu.handleInput(event);
            menu.display(game.renderer);
            SDL_SetRenderDrawColor(game.renderer, 255,255,255,255);
        }

        if(state == EXIT){
            game.running = false;
        }

        if(state == GAME){
        	//a
            machete.handle_events(event);
            aim.handle_events(event, bullet, audio);
            for(unsigned int i = 0; i<enemies.size(); i++){
                enemies[i]->handle_events(event, aim, bullet, particles);
            }
            particles.handle_events(event, aim.isAiming());

            SDL_SetRenderDrawColor(game.renderer, 220, 198, 160,0);
            SDL_RenderFillRect(game.renderer, &sand);

            SDL_SetRenderDrawColor(game.renderer, 0,0,0,255);

            hurt = false;
            for(unsigned int i = 0; i<enemies.size(); i++){
                if(enemies[i]->hurt(aim.life, frames) && enemies[i]->isActive()){
                    if(!aim.isAiming()){
    //                    std::cout << "life: " << life << "\n";
                        if(aim.life == 0)
                            std::cout << "life: " << aim.life << ". Death." << "\n";
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

            if(aim.getMeters() < 4700){
                SDL_SetRenderDrawColor(game.renderer, 125,125,0,0);
                SDL_RenderFillRect(game.renderer, &goal);
            }

            aim.draw(game.renderer);
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

            if(aim.life == 0){
                state = MENU;
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

                if(aim.getMeters() > 1500){
                    for(int i = 0; i<10; i++){
                        enemies.push_back(new Enemy((rand()%sw), (500/2)+15, 1, 5, (rand()%5)+1, Texture(enems[rand()%3])));
                        totalenemies++;
                    }
                }
            }
        }


        SDL_RenderPresent(game.renderer);
    }

    game.clean();

    return 0;
}
