#ifndef AUDIO_H
#define AUDIO_H

#include <vector>
#include <SDL2/SDL_mixer.h>


class Sound
{
   public:
   //Constructo/ Destructor
    Sound(int MaxChannel);
    ~Sound();
    // Method
    void PlaySound(int channelNumber, int effectNumber); // Plays specified sound effect.

    // enumerations for sound effect 
    enum Channels {chchSnake, chGame };
    enum SoundEffects { sndEatFood, sndGameOver};

   private:
   //Private Method
    void LoadSound(); // Loads Sound Effects

    //Private members
    int const _numChannels; // Number of channels 
    Mix_Chunk *_audio[2]; // audio chunk object 
};

#endif