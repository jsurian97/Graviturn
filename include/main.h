/* main.h */
#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

//music
void play_music_loop(const char *filepath);
void stop_music();

#endif // MAIN_H
