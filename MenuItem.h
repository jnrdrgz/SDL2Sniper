#ifndef MENUITEM_H
#define MENUITEM_H

#include <SDL2/SDL.h>
#include "string"


class MenuItem
{
    public:
        MenuItem();
        MenuItem(std::string t, unsigned char r, unsigned char b, unsigned char g);
        std::string text;
        SDL_Texture* texture;
        bool selected;
        SDL_Color color;
    private:


};

#endif // MENUITEM_H
