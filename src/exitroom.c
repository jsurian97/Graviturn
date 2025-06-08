#include "main.h"

// Renvoie 1 si shapePerso intersecte shapeSortie, 0 sinon
int Sortie(SDL_FRect *shapePerso, SDL_FRect *shapeSortie)
{
    // Coordonnées du perso
    float pLeft   = shapePerso->x;
    float pRight  = shapePerso->x + shapePerso->w;
    float pTop    = shapePerso->y;
    float pBottom = shapePerso->y + shapePerso->h;

    // Coordonnées de la sortie
    float sLeft   = shapeSortie->x;
    float sRight  = shapeSortie->x + shapeSortie->w;
    float sTop    = shapeSortie->y;
    float sBottom = shapeSortie->y + shapeSortie->h;

    // Test AABB : pas de collision si une des conditions suivantes est vraie
    if (pRight  < sLeft)   return 0;
    if (pLeft   > sRight)  return 0;
    if (pBottom < sTop)    return 0;
    if (pTop    > sBottom) return 0;

    // Sinon, rectangles se chevauchent
    return 1;
}

