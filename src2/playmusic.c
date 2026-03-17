#include "main.h"

static Mix_Music *music = NULL;

void play_music_loop(const char *filepath)
{
    SDL_AudioSpec spec = {
        .freq = 44100,
        .format = SDL_AUDIO_S16,
        .channels = 2,
    };

    Mix_OpenAudio(0, &spec);
    music = Mix_LoadMUS(filepath);
    Mix_PlayMusic(music, -1);  // -1 = boucle infinie
}

void stop_music()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
    Mix_CloseAudio();
}

