#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Constants.h"
#include "MenuItem.h"

class Menu
{
    public:
        Menu();
        void load();
        void addItem(MenuItem* itemMenu, SDL_Renderer* r);
        void display(SDL_Renderer* r);
        int handleInput(SDL_Event e);

    private:
        std::vector<MenuItem*> items;
        TTF_Font* font = NULL;

        int selected = 0;
        bool pressed = false;
};

#endif // MENU_H
