#ifndef AUDIO_H
#define AUDIO_H

#include <vector>
#include <SDL2/SDL_mixer.h>


class Audio
{
   public:
   //Constructo/ Destructor
    Audio(int MaxChannel);
    ~Audio();
    // Method
    void PlayAudio(int channelNumber, int effectNumber); // Plays specified sound effect.

    // enumerations for sound effect 
    enum Channels {chchSnake, chGame };
    enum SoundEffects { sndEatFood, sndGameOver};

   private:
   //Private Method
    void LoadAudio(); // Loads Sound Effects

    //Private members
    int const _numChannels; // Number of channels 
    Mix_Chunk *_audio[2]; // audio chunk object 
};

#endif