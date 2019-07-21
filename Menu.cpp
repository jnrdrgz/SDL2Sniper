#include "Menu.h"

Menu::Menu()
{
    //ctor
}

void Menu::load()
{
    font = TTF_OpenFont( "assets/font.ttf", 48 );
}

void Menu::addItem(MenuItem* item, SDL_Renderer* r)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, item->text.c_str(), item->color);
    item->texture = SDL_CreateTextureFromSurface(r, textSurface);
    items.push_back(item);


    SDL_FreeSurface(textSurface);
}

void Menu::display(SDL_Renderer* r)
{
    int x = 640/2;
    int y = 0;

    for(int i = 0; i < items.size(); i++){
        SDL_Rect src = {0,0,(int)items[i]->text.length()*48,48 + 10};
        
        SDL_Rect dst = {x-75,y,src.w,50};

        SDL_RenderCopy(r, items[i]->texture, &src, &dst);
        y += dst.h;

        if(i == selected){
            SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
            SDL_Rect slct = {dst.x-20, dst.y+20, 10, 10};
            SDL_RenderFillRect(r, &slct);
        }
    }
}

//return game state
int Menu::handleInput(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
            if(!pressed){
                if(event.key.keysym.sym == SDLK_DOWN){
                    selected++;
                    if(selected >= items.size()){
                        selected = 0;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP){
                    selected -= 1;
                    if(selected < 0){
                        selected = items.size()-1;
                    }
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    return selected+1;
                }
                pressed = true;
            }
        break;
        case SDL_KEYUP:
            pressed = false;
        break;
    }

    return 0;
}

