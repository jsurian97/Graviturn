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

#define	HEIGHT	720
#define WIDTH	1280
#define NB_ROOMS 20
#define SIZE_ROOMS 400

// Directions de la gravité
enum {
    GRAVITE_BAS,
    GRAVITE_HAUT,
    GRAVITE_G,
    GRAVITE_D
};

// Structure pour la gestion du double-appui des touches
typedef struct repeatkey {
    int key_up;
    int key_down;
    int key_left;
    int key_right;
} t_rekey;

// Prototypes des fonctions de collision
int CollisionBas(SDL_FRect *perso, SDL_FRect *room);
int CollisionHaut(SDL_FRect *perso, SDL_FRect *room);
int CollisionDroite(SDL_FRect *perso, SDL_FRect *room);
int CollisionGauche(SDL_FRect *perso, SDL_FRect *room);

// Prototype pour le changement de gravité par double-appui
int changementGraviteFace(const bool *keys,
                          SDL_Scancode sc,
                          int *enGravite,
                          int *doublepress,
                          int direction,
                          int *etat_gravite);

// Prototypes des fonctions d’application de la gravité
void appliquerGraviteBas(const bool *keys,
                         SDL_FRect *shapePerso,
                         SDL_FRect *shapeRoom,
                         float *vx,
                         float *vy,
                         float saut,
                         int *enGravite,
                         float gravite,
                         int *enSaut,
                         float *sol_y,
                         t_rekey *rekey,
                         int *etat_gravite);

void appliquerGraviteHaut(const bool *keys,
                          SDL_FRect *shapePerso,
                          SDL_FRect *shapeRoom,
                          float *vx,
                          float *vy,
                          float saut,
                          int *enGravite,
                          float gravite,
                          int *enSaut,
                          float *sol_y,
                          t_rekey *rekey,
                          int *etat_gravite);

void appliquerGraviteDroite(const bool *keys,
                            SDL_FRect *shapePerso,
                            SDL_FRect *shapeRoom,
                            float *vx,
                            float *vy,
                            float saut,
                            int *enGravite,
                            float gravite,
                            int *enSaut,
                            float *sol_x,
                            t_rekey *rekey,
                            int *etat_gravite);

void appliquerGraviteGauche(const bool *keys,
                            SDL_FRect *shapePerso,
                            SDL_FRect *shapeRoom,
                            float *vx,
                            float *vy,
                            float saut,
                            int *enGravite,
                            float gravite,
                            int *enSaut,
                            float *sol_x,
                            t_rekey *rekey,
                            int *etat_gravite);
// Point d'entrée
int main(void);
int Sortie(SDL_FRect *shapePerso, SDL_FRect *shapeSortie);
int isInsideAll(SDL_FRect *perso, SDL_FRect *room, int modulo);

//music
void play_music_loop(const char *filepath);
void stop_music();

#endif // MAIN_H

