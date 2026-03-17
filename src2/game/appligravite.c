#include "main.h"

int	changementGraviteFace(const bool *keys, SDL_Scancode sc, int *enGravite, int *doublepress, int direction, int *etat_gravite)
{
	if (keys[sc] && *doublepress == 0)
		*doublepress = 1;
	if (!keys[sc] && *doublepress == 1)
		*doublepress = 2;
	if (keys[sc] && *doublepress == 2)
	{
		*etat_gravite = direction;
		*enGravite = 1;
		*doublepress = 0;
		return 1;
	}
	return 0;
}

void appliquerGraviteBas(const bool *keys, SDL_FRect *shapePerso, SDL_FRect *shapeRoom, float *vx, float *vy, float saut, int *enGravite, float gravite, int *enSaut, float *sol_y, t_rekey *rekey, int *etat_gravite)
{

	if (!*enGravite)
	{
		//printf("essaie de changer la gravite\n");

	    if (changementGraviteFace(keys, SDL_SCANCODE_UP, enGravite, &rekey->key_up, GRAVITE_HAUT, etat_gravite))
			return ;
		if (keys[SDL_SCANCODE_RIGHT] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_D;
			*enGravite = 1;
			return ;
		}
		if (keys[SDL_SCANCODE_LEFT] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_G;
			*enGravite = 1;
			return ;
		}
	}

    *sol_y = shapeRoom->y + shapeRoom->h - shapePerso->h;
    SDL_FRect temp = *shapePerso;

	if (!*enSaut && !*enGravite)
	{
    	if (keys[SDL_SCANCODE_LEFT])
		{
    	    temp.x -= 1;
			if (CollisionBas(&temp, shapeRoom))
    	        shapePerso->x = temp.x;
		}
    	if (keys[SDL_SCANCODE_RIGHT])
		{
    	    temp.x += 1;
			if (CollisionBas(&temp, shapeRoom))
    	        shapePerso->x = temp.x;
		}
    	if (keys[SDL_SCANCODE_UP])
    	{
    	    *vy -= saut;
    	    *enSaut = 1;
    	}
	}

    if (*enSaut)
    {
        *vy += gravite;              // gravité accélère la descente
        temp = *shapePerso;
        temp.x += *vx;
        if (CollisionBas(&temp, shapeRoom))
            shapePerso->x = temp.x;

        temp.y += *vy;
		if (CollisionBas(&temp, shapeRoom))
            shapePerso->y = temp.y;

        if (shapePerso->y >= *sol_y)
        {
            shapePerso->y = *sol_y;  // le remet exactement au sol
            *vy = 0;
            *vx = 0;
            *enSaut = 0;
            *enGravite = 0;
			rekey->key_left = 0;
			rekey->key_right = 0;
			rekey->key_up = 0;
        }
    }
}


void appliquerGraviteHaut(const bool *keys, SDL_FRect *shapePerso, SDL_FRect *shapeRoom, float *vx, float *vy, float saut, int *enGravite, float gravite, int *enSaut, float *sol_y, t_rekey *rekey, int *etat_gravite)
{
	if (!*enGravite)
	{
	    if (changementGraviteFace(keys, SDL_SCANCODE_DOWN, enGravite, &rekey->key_down, GRAVITE_BAS, etat_gravite))
			return ;
		if (keys[SDL_SCANCODE_RIGHT] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_D;
			*enGravite = 1;
			return ;
		}
		if (keys[SDL_SCANCODE_LEFT] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_G;
			*enGravite = 1;
			return ;
		}
	}

    *sol_y = shapeRoom->y;
    SDL_FRect temp = *shapePerso;


	if (!*enSaut && !*enGravite)
	{
    	if (keys[SDL_SCANCODE_LEFT])
		{
    	    temp.x -= 1;
			if (CollisionHaut(&temp, shapeRoom))
    	        shapePerso->x = temp.x;
		}
    	if (keys[SDL_SCANCODE_RIGHT])
		{
    	    temp.x += 1;
			if (CollisionHaut(&temp, shapeRoom))
    	        shapePerso->x = temp.x;
		}
    	if (keys[SDL_SCANCODE_DOWN] && *enSaut == 0)
    	{
    	    *vy += saut;
    	    *enSaut = 1;
    	}
	}

    if (*enSaut)
    {
        *vy -= gravite;              // gravité "vers le haut"
        temp = *shapePerso;

        temp.x += *vx;
        if (CollisionHaut(&temp, shapeRoom))
            shapePerso->x = temp.x;

        temp.y += *vy;
        if (CollisionHaut(&temp, shapeRoom))
            shapePerso->y = temp.y;

        if (shapePerso->y <= *sol_y)
        {
            shapePerso->y = *sol_y;  // le remet exactement au "plafond"
            *vy = 0;
			*vx = 0;
            *enSaut = 0;
            *enGravite = 0;
			rekey->key_right = 0;
			rekey->key_left = 0;
			rekey->key_down = 0;
        }
    }
}

void appliquerGraviteDroite(const bool *keys, SDL_FRect *shapePerso, SDL_FRect *shapeRoom, float *vx, float *vy, float saut, int *enGravite, float gravite, int *enSaut, float *sol_x, t_rekey *rekey, int *etat_gravite)
{
	if (!*enGravite)
	{
	    if (changementGraviteFace(keys, SDL_SCANCODE_LEFT, enGravite, &rekey->key_left, GRAVITE_G, etat_gravite))
			return ;
		if (keys[SDL_SCANCODE_UP] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_HAUT;
			*enGravite = 1;
			return ;
		}
		if (keys[SDL_SCANCODE_DOWN] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_BAS;
			*enGravite = 1;
			return ;
		}
	}

    *sol_x = shapeRoom->x + shapeRoom->w - shapePerso->w;
    SDL_FRect temp = *shapePerso;

	if (!*enSaut && !*enGravite)
	{
    	if (keys[SDL_SCANCODE_UP])
		{
    	    temp.y -= 1;
			if (CollisionDroite(&temp, shapeRoom))
    	        shapePerso->y = temp.y;
		}
    	if (keys[SDL_SCANCODE_DOWN])
		{
    	    temp.y += 1;
			if (CollisionDroite(&temp, shapeRoom))
    	        shapePerso->y = temp.y;
		}


	    if (keys[SDL_SCANCODE_LEFT] && *enSaut == 0)
	    {
	        *vx -= saut;
	        *enSaut = 1;
	    }
	}

    if (*enSaut)
    {
        *vx += gravite;
        temp = *shapePerso;

        temp.x += *vx;
        if (CollisionDroite(&temp, shapeRoom))
            shapePerso->x = temp.x;
		

		temp.y += *vy;
        if (CollisionDroite(&temp, shapeRoom))
            shapePerso->y = temp.y;

        if (shapePerso->x >= *sol_x)
        {
            shapePerso->x = *sol_x;
            *vx = 0;
            *vy = 0;
            *enSaut = 0;
            *enGravite = 0;
            rekey->key_left = 0;
            rekey->key_up = 0;
            rekey->key_down = 0;
        }
    }
}

void appliquerGraviteGauche(const bool *keys, SDL_FRect *shapePerso, SDL_FRect *shapeRoom, float *vx, float *vy, float saut, int *enGravite, float gravite, int *enSaut, float *sol_x, t_rekey *rekey, int *etat_gravite)
{
	if (!*enGravite)
	{
	    if (changementGraviteFace(keys, SDL_SCANCODE_RIGHT, enGravite, &rekey->key_right, GRAVITE_D, etat_gravite))
			return ;
		if (keys[SDL_SCANCODE_UP] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_HAUT;
			*enGravite = 1;
			return ;
		}
		if (keys[SDL_SCANCODE_DOWN] && *enSaut == 1)
		{
			*etat_gravite = GRAVITE_BAS;
			*enGravite = 1;
			return ;
		}
	}
    *sol_x = shapeRoom->x;
	SDL_FRect temp = *shapePerso;


	if (!*enSaut && !*enGravite)
	{
    	if (keys[SDL_SCANCODE_UP])
		{
    	    temp.y -= 1;
			if (CollisionGauche(&temp, shapeRoom))
    	        shapePerso->y = temp.y;
		}
    	if (keys[SDL_SCANCODE_DOWN])
		{
    	    temp.y += 1;
			if (CollisionGauche(&temp, shapeRoom))
    	        shapePerso->y = temp.y;
		}

    	if (keys[SDL_SCANCODE_RIGHT] && *enSaut == 0)
    	{
    	    *vx += saut;
    	    *enSaut = 1;
    	}
	}

    if (*enSaut)
    {
        *vx -= gravite;

        temp = *shapePerso;

        temp.x += *vx;
        if (CollisionGauche(&temp, shapeRoom))
            shapePerso->x = temp.x;

		temp.y += *vy;
		if (CollisionGauche(&temp, shapeRoom))
			shapePerso->y = temp.y;

        if (shapePerso->x <= *sol_x)
        {
            shapePerso->x = *sol_x;
            *vx = 0;
            *vy = 0;
            *enSaut = 0;
            *enGravite = 0;
            rekey->key_right = 0;
            rekey->key_up = 0;
            rekey->key_down = 0;
        }
    }
}
