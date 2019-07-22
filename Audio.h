#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

class Audio
{
public:
	Audio();
	~Audio();

	void MakeSoundSniper();

private:
	Mix_Chunk *sniperShot = NULL;
};

#endif