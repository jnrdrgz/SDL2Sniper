#ifndef MACHETE_H
#define MACHETE_H

#include <SDL2/SDL.h>

class Machete
{
public:
    Machete(SDL_Texture* t);

    void update();

    void draw(SDL_Renderer* r);

    void handle_events(SDL_Event event);

    bool isActive();
private:
    SDL_Rect dst;
    SDL_Texture* texture = NULL;
    bool key_press = false, active = false;

};

#endif // MACHETE_H
