#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Game
{
    public:
        Game();
        ~Game();

        void init(std::string title, int window_w, int window_h);
        void clean();

        bool running = false;

        SDL_Renderer *renderer;

    private:
        SDL_Window *window;

};

#endif // GAME_HPP
