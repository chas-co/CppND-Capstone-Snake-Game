#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include "audio.h"


    // New: Sound constructor 
    Audio::Audio(int MaxChannels):_numChannels(MaxChannels)
    {
        // initialise SDL mixer so other functions can be used 
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        {
            std::cout << "Failed to initialise SDL Mixer"<<std::endl;
        }
        // Allocate the number of channels SDL mixer will manage 
        Mix_AllocateChannels(_numChannels);
        
        // Load Sound to be used in the game
        Audio::LoadAudio();
        
    }

    // New: Sound destructor
    Audio::~Audio()
    {
        //Free Previosly Loaded audio
        Mix_FreeChunk(_audio[SoundEffects::sndEatFood]);
        Mix_FreeChunk(_audio[SoundEffects::sndGameOver]);
        Mix_Quit();
    }

    void Audio::LoadAudio()
    {
        // Load eatfood sound and check if it is loaded properly
        _audio[SoundEffects::sndEatFood] = Mix_LoadWAV("../audio/zapsplat_human_eat_potato_chip_single_bite_crunch_001_50031.wav");
        if(!_audio[SoundEffects::sndEatFood])
        {
            std::cout<< "Failed to load Sound Effect EatFood\n";
            std::cout<< "Mixer Error: "<< Mix_GetError() << "\n";
        }
        
        // Load game over sound and check if it is loaded properly
        _audio[SoundEffects::sndGameOver] = Mix_LoadWAV("../audio/zapsplat_multimedia_game_sound_musical_ending_retro_videogame_001_63029.wav");
        if(!_audio[SoundEffects::sndGameOver])
        {
            std::cout<< "Failed to load Sound Effect Gameover\n";
            std::cout<< "Mixer Error: "<< Mix_GetError() << "\n";
        }

    }

    void Audio::PlayAudio(int channelNumber, int effectNumber)
    {
        // Play specified sound effect on specified channel
        Mix_PlayChannel(channelNumber, _audio[effectNumber],0);
    }
