#include "main.h"

int Sortie(SDL_FRect *shapePerso, SDL_FRect *shapeSortie)
{
    float pLeft   = shapePerso->x;
    float pRight  = shapePerso->x + shapePerso->w;
    float pTop    = shapePerso->y;
    float pBottom = shapePerso->y + shapePerso->h;

    float sLeft   = shapeSortie->x;
    float sRight  = shapeSortie->x + shapeSortie->w;
    float sTop    = shapeSortie->y;
    float sBottom = shapeSortie->y + shapeSortie->h;

    if (pRight  < sLeft)
		return 0;
    if (pLeft   > sRight)
		return 0;
    if (pBottom < sTop)
		return 0;
    if (pTop    > sBottom)
		return 0;

    return 1;
}

