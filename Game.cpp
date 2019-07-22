#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::init(std::string title, int window_w, int window_h){
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    } else {
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        if(window_h == 0 && window_w == 0){
            window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_FULLSCREEN );
        } else{
            window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_SHOWN );
        }

		if( window == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}else{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}else{
				int imgFlags = IMG_INIT_PNG;
				int initted = IMG_Init(imgFlags);

				if( (initted&imgFlags) !=  imgFlags )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				} else {
					if (TTF_Init() < 0) {
						printf("ttf could not initialize\n");
					}
					if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                	{
                    	printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );	
                    }	

                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
					running = true;
				}
			}
		}
    }
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
