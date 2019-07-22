#include "Audio.h"

Audio::Audio(){
	sniperShot = Mix_LoadWAV("assets/sniperShot.wav");
	if(sniperShot == NULL)
		printf("error loading sound\n");
}
Audio::~Audio(){
	//Mix_FreeChunk(sniperShot);
}

void Audio::MakeSoundSniper(){
	Mix_PlayChannel( -1, sniperShot, 0 );
}