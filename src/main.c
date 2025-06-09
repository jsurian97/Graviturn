#include "main.h"

int	main()
{
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
	SDL_Window *win = SDL_CreateWindow("JAM", WIDTH, HEIGHT, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(win, NULL);

	play_music_loop("assets/music.mp3");

	SDL_Surface *surfacePerso = IMG_Load("assets/Player.png");
	
	SDL_Surface *surfaceRoom = IMG_Load("assets/MapSquare_0.png");

	SDL_Surface *surfaceSortieBlanc = IMG_Load("assets/SortieBlanc.png");
	SDL_Surface *surfaceSortieNoir = IMG_Load("assets/SortieNoir.png");

	SDL_Texture *textureRoom[NB_ROOMS];
	SDL_FRect shapeRoom[NB_ROOMS];
	int	iRoom = 0;
	int	iActRoom = 0;
	int iSortie = 1;
	int OldSortie = 0;

	SDL_Texture *texturePerso = SDL_CreateTextureFromSurface(renderer, surfacePerso);
    SDL_DestroySurface(surfacePerso);
	while (iRoom < NB_ROOMS)
	{
		textureRoom[iRoom] = SDL_CreateTextureFromSurface(renderer, surfaceRoom);
		iRoom++;
	}
    SDL_DestroySurface(surfaceRoom);

	SDL_Texture *textureSortie[2];
	textureSortie[0] = SDL_CreateTextureFromSurface(renderer, surfaceSortieNoir);
    SDL_DestroySurface(surfaceSortieNoir);
	textureSortie[1] = SDL_CreateTextureFromSurface(renderer, surfaceSortieBlanc);
    SDL_DestroySurface(surfaceSortieBlanc);

	float sizePerso = 64; //mettre un pourcentage de la size de surface adaptable a lecran
	float sizeRoom[NB_ROOMS];
	float sizeSortie = 48;

	float factorRoom[NB_ROOMS];
	iRoom = 0;
	while (iRoom < NB_ROOMS)
	{
		factorRoom[iRoom] = 1 + iRoom * 0.3;
		iRoom++;
	}
	iRoom = 0;

	while (iRoom < NB_ROOMS)
	{
		sizeRoom[iRoom] = SIZE_ROOMS * factorRoom[iRoom]; 
		iRoom++;
	}
	iRoom = 0;

	float entreRoom = sizeRoom[iRoom] * 0.15;
	//float acceleration = 1;

	SDL_FRect shapePerso =
	{	.x = WIDTH / 2 - sizePerso / 2, .y = HEIGHT / 2 - sizePerso / 2, .w = sizePerso, .h = sizePerso};
	SDL_FRect shapeSortie =
	{	.x = WIDTH / 2 - sizeSortie / 2, .y = HEIGHT / 2 - sizeSortie / 2, .w = sizeSortie, .h = sizeSortie};

	while (iRoom < NB_ROOMS) 
	{
		shapeRoom[iRoom].w = sizeRoom[iRoom];
		shapeRoom[iRoom].h = sizeRoom[iRoom];
		shapeRoom[iRoom].x = (WIDTH  - shapeRoom[iRoom].w) / 2.0f;
		shapeRoom[iRoom].y = (HEIGHT - shapeRoom[iRoom].h) / 2.0f;
		iRoom++;
	}
	iRoom = 0;

	SDL_FRect shapeFakeRoom;
	int	iCol = 0;

	//gravite
	float	vy = 0;        // vitesse verticale
	float	vx = 0;        // vitesse verticale
	float	gravite = 0.01; // force de gravité constante
	float	sol_y = 0;   // niveau du sol
	float	sol_x = 0;
	float	saut = 0.8;
	int		enSaut = 1;
	int		etat_gravite = GRAVITE_BAS;
	int		enGravite = 0;

	t_rekey repeatkey;

	repeatkey.key_up = 0;
	repeatkey.key_down = 0;
	repeatkey.key_right = 0;
	repeatkey.key_left = 0;

	SDL_Event	event;
	bool quit = false;

	SDL_Keycode key = 1;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				quit = true;
			else if (event.type == SDL_EVENT_KEY_DOWN)
			{	
				key = event.key.key;
        		if (key == 113) // q
					quit = true;
			}
			else if (event.type == SDL_EVENT_KEY_UP)
                key = 0;
		}
		
		const bool* keys = SDL_GetKeyboardState(NULL);
		//resize des rooms
		iRoom = 0;
		while (iRoom < NB_ROOMS)
		{
			factorRoom[iRoom] -= 0.00005;
			if (factorRoom[iRoom] < 0.0)
			{
				if (iRoom != 0)
					factorRoom[iRoom] = factorRoom[iRoom - 1] + 0.3;
				else
					factorRoom[iRoom] = factorRoom[NB_ROOMS - 1] + 0.3;
			}
			iRoom++;
		}
		//printf("%f\n", factorRoom[4]);
		iRoom = 0;

		while (iRoom < NB_ROOMS)
		{
			sizeRoom[iRoom] = SIZE_ROOMS * factorRoom[iRoom]; //* acceleration; 
			iRoom++;
		}
		iRoom = 0;
		while (iRoom < NB_ROOMS) 
		{
			shapeRoom[iRoom].w = sizeRoom[iRoom];
			shapeRoom[iRoom].h = sizeRoom[iRoom];
			shapeRoom[iRoom].x = (WIDTH  - shapeRoom[iRoom].w) / 2.0f;
			shapeRoom[iRoom].y = (HEIGHT - shapeRoom[iRoom].h) / 2.0f;
			iRoom++;
		}
		iRoom = 0;


		//room actuel
		entreRoom = sizeRoom[iActRoom] * 0.15;
		
		shapeFakeRoom.x = shapeRoom[iActRoom].x + entreRoom;
		shapeFakeRoom.y = shapeRoom[iActRoom].y + entreRoom;
		shapeFakeRoom.w = shapeRoom[iActRoom].w - entreRoom * 2;
		shapeFakeRoom.h = shapeRoom[iActRoom].h - entreRoom * 2;

		isInsideAll(&shapePerso, &shapeFakeRoom, iCol % 4);
		iCol++;
		if (iCol > 1000)
		{
			iCol = 0;
			if (!enSaut)
			{
				OldSortie = 0;
				if (iSortie)
					iSortie = 0;
				else 
					iSortie = 1;
			}
		}

		//SDL_FRect shapeSortie =
		//{	.x = WIDTH / 2 - sizeSortie / 2, .y = HEIGHT / 2 - sizeSortie / 2, .w = sizeSortie, .h = sizeSortie};
		//{	.x = shapeRoom[iActRoom].x + entreRoom, .y = shapeRoom[iActRoom].y + entreRoom, .w = sizeSortie, .h = sizeSortie};

		if (etat_gravite == GRAVITE_BAS)
		    appliquerGraviteBas(keys, &shapePerso, &shapeFakeRoom, &vx, &vy, saut, &enGravite, gravite, &enSaut, &sol_y, &repeatkey, &etat_gravite);

		if (etat_gravite == GRAVITE_HAUT)
		    appliquerGraviteHaut(keys, &shapePerso, &shapeFakeRoom, &vx, &vy, saut, &enGravite, gravite, &enSaut, &sol_y, &repeatkey, &etat_gravite);

		if (etat_gravite == GRAVITE_G)
			appliquerGraviteGauche(keys, &shapePerso, &shapeFakeRoom, &vx, &vy, saut, &enGravite, gravite, &enSaut, &sol_x, &repeatkey, &etat_gravite);

		if (etat_gravite == GRAVITE_D)
			appliquerGraviteDroite(keys, &shapePerso, &shapeFakeRoom, &vx, &vy, saut, &enGravite, gravite, &enSaut, &sol_x, &repeatkey, &etat_gravite);

		if	(Sortie(&shapePerso, &shapeSortie) && iSortie == 1 && OldSortie == 0)	//changer la room principal
		{
			iActRoom++;
			enSaut = 1;
			OldSortie = 1;
			//acceleration += 0.01;
		}
		if	(Sortie(&shapePerso, &shapeSortie) && iSortie == 0)	//game_over
		{
			break;
		}
		if (iActRoom == NB_ROOMS)
			iActRoom = 0;	

		SDL_RenderClear(renderer);
		iRoom = 0;
		while (iRoom < NB_ROOMS)
		{
			SDL_RenderTexture(renderer, textureRoom[iRoom], NULL, &shapeRoom[iRoom]);
			iRoom++;
		}
		iRoom = 0;
		SDL_RenderTexture(renderer, textureSortie[iSortie], NULL, &shapeSortie);
		SDL_RenderTexture(renderer, texturePerso, NULL, &shapePerso);
		SDL_RenderPresent(renderer);
		usleep(500);
	}

	SDL_DestroyTexture(texturePerso);
	SDL_DestroyTexture(textureSortie[0]);
	SDL_DestroyTexture(textureSortie[1]);
	iRoom = 0;
	while (iRoom < NB_ROOMS)
	{
		SDL_DestroyTexture(textureRoom[iRoom]);
		iRoom++;
	}
	stop_music();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	SDL_Quit();
	return 0;
}
