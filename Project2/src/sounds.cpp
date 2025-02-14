#include "sounds.h"

static void loadSounds(void);
void initSound(void)
{
    memset(sounds,0,sizeof(Mix_Chunk*)*SND_MAX);
    loadSounds();
}

static void loadSounds(void)
{
    sounds[SND_PF] = Mix_LoadWAV("sound/334227__jradcoolness__laser.ogg");
    sounds[SND_AF] = Mix_LoadWAV("sound/196914__dpoggioli__laser-gun.ogg");
    sounds[SND_PD] = Mix_LoadWAV("sound/245372__quaker540__hq-explosion.ogg");
    sounds[SND_AD] = Mix_LoadWAV("sound/10 Guage Shotgun-SoundBible.com-74120584.ogg");
}

void loadMusic(char* filename)
{
    if(music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
    Mix_PlayMusic(music,(loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
    Mix_PlayChannel(channel,sounds[id],0);
}
