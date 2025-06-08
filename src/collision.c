#include "main.h"

int	isInsideAll(SDL_FRect *perso, SDL_FRect *room, int modulo)
{
    float persoLeft = perso->x;
    float persoRight = perso->x + perso->w;
	float persoTop = perso->y;
	float persoBottom = perso->y + perso->h;

    float roomLeft = room->x;
    float roomRight = room->x + room->w;
	float roomTop = room->y;
	float roomBottom = room->y + room->h;

    if (persoRight > roomRight && modulo == 0) // A à gauche de B
    { 
		perso->x = roomRight - perso->w;
		return 0;
	}
    if (persoLeft < roomLeft && modulo == 1) // A à droite de B
	{
		perso->x = roomLeft;
        return 0;
	}
    if (persoTop < roomTop && modulo == 2) // A au-dessus de B
	{
		perso->y = roomTop;
        return 0;
	}
	if (persoBottom > roomBottom && modulo == 3) // A au-dessus de B
	{
		perso->y = roomBottom - perso->h;
		return 0;
	}

    return 1; // Collision détectée

}

int	CollisionBas(SDL_FRect *perso, SDL_FRect *room)
{
    float persoLeft = perso->x;
    float persoRight = perso->x + perso->w;
	float persoTop = perso->y;

    float roomLeft = room->x;
    float roomRight = room->x + room->w;
	float roomTop = room->y;

    if (persoRight > roomRight) // A à gauche de B
    { 
		perso->x = roomRight - perso->w;
		return 0;
	}
    if (persoLeft < roomLeft) // A à droite de B
	{
		perso->x = roomLeft;
        return 0;
	}
    if (persoTop < roomTop) // A au-dessus de B
	{
		perso->y = roomTop;
        return 0;
	}

    return 1; // Collision détectée
}

int	CollisionHaut(SDL_FRect *perso, SDL_FRect *room)
{
    float persoLeft = perso->x;
    float persoRight = perso->x + perso->w;
	float persoBottom = perso->y + perso->h;

    float roomLeft = room->x;
    float roomRight = room->x + room->w;
	float roomBottom = room->y + room->h;


    if (persoRight > roomRight) // A à gauche de B
	{
		perso->x = roomRight - perso->w;
        return 0;
	}

    if (persoLeft < roomLeft) // A à droite de B
    {
		perso->x = roomLeft;
		return 0;
	}

	if (persoBottom > roomBottom) // A au-dessus de B
	{
		perso->y = roomBottom - perso->h;
		return 0;
	}

    return 1; // Collision détectée
}

int	CollisionDroite(SDL_FRect *perso, SDL_FRect *room)
{
    float persoTop = perso->y;
    float persoBottom = perso->y + perso->h;
	float persoLeft = perso->x;

    float roomTop = room->y;
    float roomBottom = room->y + room->h;
	float roomLeft = room->x;


    if (persoTop < roomTop) // A à gauche de B
	{
		perso->y = roomTop;
        return 0;
	}

    if (persoBottom > roomBottom) // A à droite de B
    {
		perso->y = roomBottom - perso->h;
		return 0;
	}

	if (persoLeft < roomLeft) // A au-dessus de B
	{
		perso->x = roomLeft;
		return 0;
	}

    return 1; // Collision détectée
}

int	CollisionGauche(SDL_FRect *perso, SDL_FRect *room)
{
    float persoTop = perso->y;
    float persoBottom = perso->y + perso->h;
	float persoRight = perso->x + perso->w;

    float roomTop = room->y;
    float roomBottom = room->y + room->h;
	float roomRight = room->x + room->w;


    if (persoTop < roomTop) // A à gauche de B
    {
		perso->y = roomTop;
		return 0;
	}

    if (persoBottom > roomBottom) // A à droite de B
	{
		perso->y = roomBottom - perso->h;
		return 0;
	}

	if (persoRight > roomRight) // A au-dessus de B
	{
		perso->x = roomRight - perso->w;
		return 0;
	}

    return 1; // Collision détectée
}
