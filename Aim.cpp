#include "Aim.h"

void Aim::draw(SDL_Renderer* r){
    if(aiming){
        SDL_RenderCopy(r, texture, NULL, &dst);
    }
}


void Aim::handle_events(SDL_Event event, Bullet& bullet){
        switch (event.type)
        {
            case SDL_KEYDOWN:
                keyPressed = true;

                    switch(event.key.keysym.sym){
                        keyPressed = true;
                        case SDLK_w:
                            if(meters > 0){
                                meters -= 2;
                                if(meters %100 == 0){
                                    std::cout << "meters left: " << meters << "\n";
                                }

                                if(meters < 4700){
                                    if((meters/2)%100 == 0){
            //                            goal.h += 3;
            //                            goal.y -= 3;
                                    }
                                }
                            }

                            if(meters == 0){
                                std::cout << "YOU REACH THE GOAL"  << "\n";
                            }
                            keyPressed = false;
                        break;

                        case SDLK_r:
                            if(cartuchos > 0){
                                cartuchos--;
                                std::cout << "carts: " << cartuchos << "\n";
                                bullets = 5;

                            } else {
                                std::cout << "RUN" << "\n";
                            }
                        break;
                    }


            break;

            case SDL_KEYUP:
                keyPressed = false;
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(!buttonPressed){
                    buttonPressed = true;
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        if(aiming == false){
                            aiming = true;
                        } else if(aiming == true){
                            aiming = false;
                        }

                        buttonPressed = true;
                    }

                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_Log("shot");
                        if(bullets > 0){
                            bullet.setxy(event.button.x,event.button.y);
                            bullet.change_state();

                            if(bullet.isActive()){
                                bullet.change_state();
                            }

                            buttonPressed = true;
                            bullets--;
                            std::cout << "bullets: " << bullets << "\n";

                            aiming = false;
                        } else {
                            std::cout << "Out of ammo. Press R.\n";
                        }
                    }
                }
            break;

            case SDL_MOUSEBUTTONUP:
                buttonPressed = false;
            break;


            case SDL_MOUSEMOTION:
                dst.x = event.button.x-1200;
                dst.y = event.button.y-1200;
            break;

        }
    }
