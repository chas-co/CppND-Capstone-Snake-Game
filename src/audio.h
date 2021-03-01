#ifndef AUDIO_H
#define AUDIO_H

#include <vector>
#include <SDL2/SDL_mixer.h>


class Sound
{
   public:
    Sound(int MaxChannel);
    ~Sound();
    
    void PlaySound(int channelNumber, int effectNumber);
    enum Channels { chSnake, chGame };
    enum SoundEffects { sndEatFood, sndGameOver};

   private:
    void LoadSound();
    int const _numChannels;
    Mix_Chunk *_sounds[2];
};

#endif