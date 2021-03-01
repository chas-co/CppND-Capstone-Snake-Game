#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include "audio.h"



    Sound::Sound(int MaxChannels):_numChannels(MaxChannels)
    {
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        {
            std::cout << "Failed to initialise SDL Mixer"<<std::endl;
        }
        Mix_AllocateChannels(_numChannels);
        memset(_sounds, 0, sizeof(Mix_Chunk*) * 2);
        Sound::LoadSound();
        
    }
    Sound::~Sound()
    {
        Mix_FreeChunk(_sounds[SoundEffects::sndEatFood]);
        Mix_FreeChunk(_sounds[SoundEffects::sndGameOver]);
        Mix_Quit();
    }

    void Sound::LoadSound()
    {
        _sounds[SoundEffects::sndEatFood] = Mix_LoadWAV("audio/zapsplat_human_eat_potato_chip_single_bite_crunch_001_50031.wav");
        if(!_sounds[SoundEffects::sndEatFood])
        {
            std::cout<< "Failed to load Sound Effect EatFood\n";
            std::cout<< "Mixer Error: "<< Mix_GetError() << "\n";
        }
        _sounds[SoundEffects::sndGameOver] = Mix_LoadWAV("audio/zapsplat_multimedia_game_sound_musical_ending_retro_videogame_001_63029.wav");
        if(!_sounds[SoundEffects::sndGameOver])
        {
            std::cout<< "Failed to load Sound Effect Gameover\n";
            std::cout<< "Mixer Error: "<< Mix_GetError() << "\n";
        }

    }

    void Sound:: PlaySound(int channelNumber, int effectNumber)
    {
        Mix_PlayChannel(channelNumber, _sounds[effectNumber],0);
    }

int main(){

    Sound sound(6);
    while(1)
    {
        sound.PlaySound(1,1);
    }
    return 0;
}
   
